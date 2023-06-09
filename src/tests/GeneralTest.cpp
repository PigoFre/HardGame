#include "TestShared.h"
#include "common/URI.h"
#include "common/String.h"
#include "common/Log.h"
#include "common/KeyValueParser.h"
#include "common/MapManager.h"
#include "common/FileSystem.h"
#include "common/ConfigPersisterSQL.h"

class GeneralTest: public AbstractTest {
};

TEST_F(GeneralTest, testStringTrim)
{
	ASSERT_EQ("foo bar", string::trim(" foo bar "));
	ASSERT_EQ("foo   bar", string::trim("  foo   bar   "));
}

TEST_F(GeneralTest, testStringCutBeforeLastMatch)
{
	std::string test("foo/bar");
	test = string::cutBeforeLastMatch(test, "/");
	ASSERT_EQ("bar", test);
}

TEST_F(GeneralTest, testStringWhitespaceMatches)
{
	std::string test("foo/bar.txt");
	ASSERT_TRUE(string::matches("foo*", test));
	ASSERT_TRUE(string::matches("*bar*", test));
	ASSERT_TRUE(string::matches("fo?/bar.txt", test));
	ASSERT_FALSE(string::matches("*foobar*", test));
}

TEST_F(GeneralTest, testStringLTrim)
{
	ASSERT_EQ("foo bar ", string::ltrim(" foo bar "));
}

TEST_F(GeneralTest, testStringRTrim)
{
	ASSERT_EQ(" foo bar", string::rtrim(" foo bar "));
}

TEST_F(GeneralTest, testKeyValueParser)
{
	KeyValueParser p("key1=value1,key2=value2,key3=true,key4=1,key5=1.1");
	ASSERT_EQ(std::string("value1"), p.getString("key1"));
	ASSERT_EQ(std::string("value2"), p.getString("key2"));
	EXPECT_TRUE(p.getBool("key3"));
	ASSERT_EQ(1, p.getInt("key4"));
	ASSERT_EQ(1.1f, p.getFloat("key5"));
}

TEST_F(GeneralTest, testMapManager)
{
	LUAMapManager mgr;
	mgr.init();
}

TEST_F(GeneralTest, testURI)
{
	{
		const URI uri("http://www.someurl.com");
		ASSERT_EQ(std::string("http"), uri.getProtocol());
		ASSERT_EQ(std::string("www.someurl.com"), uri.getHost());
		ASSERT_EQ(std::string(""), uri.getPort());
		ASSERT_EQ(std::string(""), uri.getPath());
		ASSERT_EQ(std::string(""), uri.getQuery());
	}
	{
		const URI uri("http://www.someurl.com/with/path");
		ASSERT_EQ(std::string("http"), uri.getProtocol());
		ASSERT_EQ(std::string("www.someurl.com"), uri.getHost());
		ASSERT_EQ(std::string("/with/path"), uri.getPath());
		ASSERT_EQ(std::string(""), uri.getPort());
		ASSERT_EQ(std::string(""), uri.getQuery());
	}
	{
		const URI uri("http://www.someurl.com:80/with/path");
		ASSERT_EQ(std::string("http"), uri.getProtocol());
		ASSERT_EQ(std::string("www.someurl.com"), uri.getHost());
		ASSERT_EQ(std::string("80"), uri.getPort());
		ASSERT_EQ(std::string("/with/path"), uri.getPath());
		ASSERT_EQ(std::string(""), uri.getQuery());
	}
	{
		const URI uri("http://www.someurl.com:80/with/path?query");
		ASSERT_EQ(std::string("http"), uri.getProtocol());
		ASSERT_EQ(std::string("www.someurl.com"), uri.getHost());
		ASSERT_EQ(std::string("80"), uri.getPort());
		ASSERT_EQ(std::string("/with/path"), uri.getPath());
		ASSERT_EQ(std::string("?query"), uri.getQuery());
	}
	{
		const URI uri("www.someurl.com:80/with/path?query");
		ASSERT_EQ(std::string(""), uri.getProtocol());
		ASSERT_EQ(std::string("www.someurl.com"), uri.getHost());
		ASSERT_EQ(std::string("80"), uri.getPort());
		ASSERT_EQ(std::string("/with/path"), uri.getPath());
		ASSERT_EQ(std::string("?query"), uri.getQuery());
	}
	{
		const URI uri("file:///with/path?query");
		ASSERT_EQ(std::string("file"), uri.getProtocol());
		ASSERT_EQ(std::string(""), uri.getHost());
		ASSERT_EQ(std::string(""), uri.getPort());
		ASSERT_EQ(std::string("/with/path"), uri.getPath());
		ASSERT_EQ(std::string("?query"), uri.getQuery());
		ASSERT_EQ(std::string("file:///with/path?query"), uri.print());
	}
}

TEST_F(GeneralTest, testConfigPersister)
{
	const std::string path = FS.getAbsoluteWritePath() + "testconfigcp.sqlite";
	FS.deleteFile(path);
	ConfigPersisterSQL persister(path);
	persister.init();
	std::map<std::string, ConfigVarPtr> configVars;
	configVars["test"] = ConfigVarPtr(new ConfigVar("test", "testvalue"));
	configVars["testnosave"] = ConfigVarPtr(new ConfigVar("testnosave", "testvalue", CV_NOPERSIST));
	persister.save(configVars);

	persister.init();
	ASSERT_EQ("testvalue", persister.getValue("test"));
	ASSERT_EQ("", persister.getValue("testnosave"));
}
