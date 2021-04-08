#include "TextureDefinition.h"
#include "common/ConfigManager.h"
#include "common/Log.h"
#include "common/LUALibrary.h"
#include "common/System.h"
#include "common/FileSystem.h"
#include "common/ExecutionTime.h"
#include "common/IProgressCallback.h"

TextureDefinition::TextureDefinition (const std::string& textureSize, IProgressCallback* progress) :
		_textureSize(textureSize), _cnt(0)
{
	if (textureSize != "big" && textureSize != "small") {
		System.exit("invalid texturesize value given: " + textureSize + ". Valid values are: auto, big, small", 1);
	}

	ExecutionTime e("Texture definition loading for " + textureSize);

	const std::string& path = FS.getTexturesDir();
	const DirectoryEntries& entries = FS.listDirectory(path);
	LUA lua;
	for (const std::string& entry : entries) {
		const std::string filename = path + entry;
		if (!FS.hasExtension(filename, "lua"))
			continue;
		if (!lua.load(filename)) {
			Log::error(LOG_COMMON, "failed to load textures from %s", filename.c_str());
			continue;
		}
		LUA_checkStack2(lua.getState());
		if (!lua.getGlobalKeyValue("textures" + textureSize))
			continue;

		while (lua.getNextKeyValue()) {
			LUA_checkStack2(lua.getState());
			std::string id = lua.getKey();
			if (id.empty()) {
				lua.pop();
				System.exit("Invalid texture entry found - invalid id", 1);
			}

			id = string::cutBeforeLastMatch(id, "/");

			if (progress != nullptr) {
				progress->progressStep();
			}
			const std::string& name = lua.getValueStringFromTable("image");
			const float x0 = lua.getValueFloatFromTable("x0");
			const float y0 = lua.getValueFloatFromTable("y0");
			const float x1 = lua.getValueFloatFromTable("x1");
			const float y1 = lua.getValueFloatFromTable("y1");
			const int trimmedWidth = lua.getValueIntegerFromTable("trimmedwidth");
			const int trimmedHeight = lua.getValueIntegerFromTable("trimmedheight");
			const int untrimmedWidth = lua.getValueIntegerFromTable("untrimmedwidth");
			const int untrimmedHeight = lua.getValueIntegerFromTable("untrimmedheight");
			const int trimmedOffsetX = lua.getValueIntegerFromTable("trimmedoffsetx");
			const int trimmedOffsetY = lua.getValueIntegerFromTable("trimmedoffsety");
			const TextureDefinitionTrim trim(trimmedWidth, trimmedHeight,
					untrimmedWidth, untrimmedHeight, trimmedOffsetX, trimmedOffsetY);
			const TextureDefinitionCoords r = { x0, y0, x1, y1 };

			if (string::contains(id, TEXTURE_DIRECTION)) {
				const std::string rightID = string::replaceAll(id, TEXTURE_DIRECTION, TEXTURE_DIRECTION_RIGHT);
				create(name, rightID, r, trim, false);
				const std::string leftID = string::replaceAll(id, TEXTURE_DIRECTION, TEXTURE_DIRECTION_LEFT);
				create(name, leftID, r, trim, true);
			} else {
				const bool mirror = lua.getValueBoolFromTable("mirror");
				create(name, id, r, trim, mirror);
			}
			lua.pop();
			++_cnt;
		}
	}

	if (_textureDefs.empty())
		Log::info(LOG_COMMON, "could not load any texture definition");
	Log::info(LOG_COMMON, "loaded %i texture definitions", (int)_textureDefs.size());
}

TextureDefinition::~TextureDefinition ()
{
	_textureDefs.clear();
}

void TextureDefinition::create (const std::string& textureName, const std::string& id, const TextureDefinitionCoords& texcoords,
		const TextureDefinitionTrim& trim, bool mirror)
{
	if (_textureDefs.find(id) != _textureDefs.end()) {
		Log::error(LOG_COMMON, "texture def with same name found: %s", id.c_str());
		return;
	}

	if (!texcoords.isValid()) {
		Log::error(LOG_COMMON, "texture def has invalid texcoords: %s", id.c_str());
		return;
	}

	const TextureDef d = {textureName, id, texcoords, trim, mirror};
	_textureDefs[id] = d;
}

const TextureDef& TextureDefinition::getTextureDef (const std::string& textureName) const
{
	TextureDefMapConstIter i = _textureDefs.find(textureName);
	if (i != _textureDefs.end()) {
		return i->second;
	}

	return _emptyTextureDef;
}

bool TextureDefinition::exists (const std::string& textureName) const
{
	TextureDefMapConstIter i = _textureDefs.find(textureName);
	if (i != _textureDefs.end()) {
		return true;
	}

	return false;
}
