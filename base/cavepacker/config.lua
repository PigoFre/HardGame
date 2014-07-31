function isMobile()
	return (isAndroid() or isIOS()) and not isOUYA();
end

defaultwidth = -1
defaultheight = -1
defaultfullscreen = false
defaultpersister = "sqlite"
defaultfrontend = "sdl"
defaultsoundengine = "sdl"
defaultshowcursor = true
defaultjoystick = false
defaulttexturesize = "small"
defaultparticles = 100

if isOUYA() then
	defaultjoystick = true
	defaultparticles = 0
elseif isMobile() then
	defaultshowcursor = false
	defaultparticles = 0
elseif isHTML5() then
	defaultpersister = "nop"
	defaultfrontend = "opengl"
	defaultsoundengine = "dummy"
else
	-- workaround for now - remove me later
	defaultfrontend = "opengl"
	defaultjoystick = true
end

settings = {
	width = defaultwidth,
	height = defaultheight,
	fullscreen = defaultfullscreen,
	frontend = defaultfrontend,
	port = 45678,
	grabmouse = true,
	showcursor = defaultshowcursor,
	debug = false,
	showfps = not isMobile(),
	joystick = defaultjoystick,
	sound = true,
	soundengine = defaultsoundengine,
	persister = defaultpersister,
	network = false,
	texturesize = defaulttexturesize,
	particles = defaultparticles,
}

controllerbindings = {
	["ui"] = {
		--A = "drop",
		--B = "",
		X = "ui_execute",
		Y = "ui_focus_next",
		BACK = "ui_pop",
		--GUIDE = "",
		--START = "",
		--LEFTSTICK = "",
		--RIGHTSTICK = "",
		--LEFTSHOULDER = "",
		--RIGHTSHOULDER = "",
		--DPUP = "",
		--DPDOWN = "",
		--DPLEFT = "",
		--DPRIGHT = "",
	},
	["map"] = {
		A = "ui_pop",
		--B = "",
		--X = "ui_execute",
		--Y = "ui_focus_next",
		--BACK = "ui_pop",
		--GUIDE = "",
		--START = "",
		--LEFTSTICK = "",
		--RIGHTSTICK = "",
		--LEFTSHOULDER = "",
		--RIGHTSHOULDER = "",
		--DPUP = "",
		--DPDOWN = "",
		--DPLEFT = "",
		--DPRIGHT = "",
	},
}

if isOUYA() then
	joystickbindings = {
		["ui"] = {
			JOY0 = "ui_focus_prev",
			JOY1 = "ui_focus_next",
			JOY2 = "ui_focus_prev",
			JOY3 = "ui_focus_next",
			JOY5 = "ui_execute",
			JOY6 = "ui_pop",
			JOY8 = "ui_focus_next",
		},
		["map"] = {
			JOY0 = "+move_up",
			JOY1 = "+move_down",
			JOY2 = "+move_left",
			JOY3 = "+move_right",
			JOY4 = "ui_pop",
			JOY5 = "ui_execute",
			JOY6 = "ui_pop",
			JOY7 = "ui_pop",
			JOY8 = "ui_pop",
			JOY9 = "ui_pop",
			JOY11 = "ui_pop",
			JOY12 = "ui_pop",
			JOY13 = "ui_pop",
			JOY14 = "ui_pop",
		},
	}
else
	joystickbindings = {
		["ui"] = {},
		["map"] = {},
	}
end

if isMobile() or isOUYA() then
	keybindings = {
		["ui"] = {
			AC_BACK = "ui_pop",
		},
		["map"] = {
			MENU = "ui_push settings",
			AC_BACK = "ui_pop",
		},
	}

	if isOUYA() then
		keybindings["ui"]["PAUSE"] = "ui_pop"
		keybindings["map"]["PAUSE"] = "ui_pop"
	end
else
	keybindings = {
		["ui"] = {
			LEFT = "ui_focus_prev",
			RIGHT = "ui_focus_next",
			UP = "ui_focus_prev",
			DOWN = "ui_focus_next",
			SPACE = "ui_execute",
			RETURN = "ui_execute",
			ESCAPE = "ui_pop",
			TAB = "ui_focus_next",
		},
		["map"] = {
			LEFT = "+move_left",
			RIGHT = "+move_right",
			UP = "+move_up",
			DOWN = "+move_down",
			SPACE = "ui_pop",
			RETURN = "ui_pop",
			ESCAPE = "ui_pop",
			TAB = "ui_focus_next",
		},
	}

	keybindings["map"]["U"] = "undo"

	if isDebug() then
		keybindings["ui"]["."] = "screenshot"
		keybindings["map"]["."] = "screenshot"
		keybindings["map"]["F"] = "finish"
		keybindings["map"]["S"] = "solve"
	end
end

