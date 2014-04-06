function getName()
	return "Flying"
end

function onMapLoaded()
end

function initMap()
	-- get the current map context
	local map = Map.get()
	map:addTile("tile-rock-02", 0, 0)
	map:addTile("tile-rock-01", 0, 1)
	map:addTile("tile-rock-left-04", 0, 2)
	map:addTile("tile-ground-06", 0, 3)
	map:addTile("tile-background-03", 0, 4)
	map:addTile("tile-ground-01", 0, 5)
	map:addTile("tile-rock-02", 1, 0)
	map:addTile("tile-rock-slope-right-02", 1, 1)
	map:addTile("tile-background-03", 1, 2)
	map:addTile("tile-ground-05", 1, 3)
	map:addTile("tile-background-04", 1, 4)
	map:addTile("tile-background-02", 1, 5)
	map:addTile("bridge-wall-left-01", 1, 5)
	map:addTile("tile-background-04", 2, 0)
	map:addTile("tile-background-04", 2, 1)
	map:addTile("tile-background-03", 2, 2)
	map:addTile("tile-background-04", 2, 3)
	map:addTile("tile-background-04", 2, 4)
	map:addTile("tile-background-02", 2, 5)
	map:addTile("bridge-wall-right-01", 2, 5)
	map:addTile("tile-background-03", 3, 0)
	map:addTile("tile-background-04", 3, 1)
	map:addTile("tile-background-03", 3, 2)
	map:addTile("tile-ground-ledge-left-02", 3, 3)
	map:addTile("tile-background-04", 3, 4)
	map:addTile("tile-ground-03", 3, 5)
	map:addTile("tile-background-04", 4, 0)
	map:addTile("tile-background-03", 4, 1)
	map:addTile("tile-background-04", 4, 2)
	map:addTile("tile-ground-ledge-right-02", 4, 3)
	map:addTile("tile-background-04", 4, 4)
	map:addTile("tile-ground-04", 4, 5)
	map:addTile("tile-background-04", 5, 0)
	map:addTile("tile-background-03", 5, 1)
	map:addTile("tile-background-04", 5, 2)
	map:addTile("tile-background-04", 5, 3)
	map:addTile("tile-background-03", 5, 4)
	map:addTile("tile-packagetarget-rock-01-idle", 5, 5)
	map:addTile("tile-rock-slope-left-02", 6, 0)
	map:addTile("tile-background-01", 6, 1)
	map:addTile("tile-background-03", 6, 2)
	map:addTile("tile-ground-ledge-left-02", 6, 3)
	map:addTile("tile-background-04", 6, 4)
	map:addTile("tile-ground-01", 6, 5)
	map:addTile("tile-rock-01", 7, 0)
	map:addTile("tile-rock-03", 7, 1)
	map:addTile("tile-rock-01", 7, 2)
	map:addTile("tile-rock-03", 7, 3)
	map:addTile("tile-rock-big-01", 7, 4)
	map:addTile("tile-rock-03", 8, 0)
	map:addTile("tile-rock-big-01", 8, 1)
	map:addTile("tile-rock-02", 8, 3)
	map:addTile("tile-rock-02", 9, 0)
	map:addTile("tile-rock-03", 9, 3)
	map:addTile("tile-rock-02", 9, 4)
	map:addTile("tile-rock-02", 9, 5)

	-- the time when the flying npc is exactly hit by the falling stone
	if isAndroid() or isOUYA() then
		map:addEmitter("item-stone", 2, 0, 1, 2700, "")
	else
		map:addEmitter("item-stone", 2, 0, 1, 2000, "")
	end
	map:addEmitter("item-package", 5.2, 0, 1, 2500, "")

	map:setSetting("fishnpc", "false")
	map:setSetting("flyingnpc", "true")
	map:setSetting("gravity", "9.81")
	map:setSetting("height", "6")
	map:setSetting("initialspawntime", "0")
	map:setSetting("packagetransfercount", "1")
	map:setSetting("playerX", "0")
	map:setSetting("playerY", "4")
	map:setSetting("points", "100")
	map:setSetting("referencetime", "20")
	map:setSetting("theme", "rock")
	map:setSetting("tutorial", "true")
	map:setSetting("waterheight", "0.5")
	map:setSetting("waterchangespeed", "0")
	map:setSetting("waterrisingdelay", "0")
	map:setSetting("width", "10")
	map:setSetting("wind", "0")
end
