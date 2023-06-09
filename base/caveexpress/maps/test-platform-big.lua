function getName()
	return "�test platform"
end

function onMapLoaded()
end

function initMap()
	-- get the current map context
	local map = Map.get()
	map:addTile("tile-background-ice-cave-art-01", 0, 0)
	map:addTile("tile-background-ice-cave-art-02", 0, 1)
	map:addTile("tile-ground-ice-big-01", 0, 2)
	map:addTile("tile-background-ice-06", 1, 0)
	map:addTile("tile-background-ice-04", 1, 1)
	map:addTile("tile-background-ice-01", 2, 0)
	map:addTile("tile-background-ice-04", 2, 1)
	map:addTile("tile-packagetarget-ice-01-idle", 2, 2)
	map:addTile("tile-background-ice-07", 2, 3)
	map:addTile("tile-background-ice-03", 3, 0)
	map:addTile("tile-background-ice-08", 3, 1)
	map:addTile("tile-ground-ledge-ice-right-01", 3, 2)
	map:addTile("tile-background-ice-cave-art-02", 3, 3)
	map:addTile("tile-background-ice-big-01", 4, 0)
	map:addTile("tile-ground-ledge-ice-right-02", 4, 2)
	map:addTile("tile-background-ice-04", 4, 3)
	map:addTile("tile-ground-ice-05", 5, 2)
	map:addTile("tile-background-ice-02", 5, 3)
	map:addTile("tile-background-ice-05", 6, 0)
	map:addTile("tile-background-ice-02", 6, 1)
	map:addTile("tile-ground-ledge-ice-left-02", 6, 2)
	map:addTile("tile-background-ice-01", 6, 3)
	map:addTile("tile-background-ice-01", 7, 0)
	map:addTile("tile-background-ice-04", 7, 1)
	map:addTile("tile-background-ice-07", 7, 2)
	map:addTile("bridge-wall-ice-left-01", 7, 2)
	map:addTile("tile-background-ice-08", 7, 3)
	map:addTile("tile-background-ice-08", 8, 0)
	map:addTile("tile-background-ice-cave-art-02", 8, 1)
	map:addTile("tile-background-ice-01", 8, 2)
	map:addTile("bridge-plank-ice-01", 8, 2)
	map:addTile("tile-background-ice-04", 8, 3)
	map:addTile("tile-background-ice-02", 9, 0)
	map:addTile("tile-background-ice-03", 9, 1)
	map:addTile("tile-background-ice-cave-art-02", 9, 2)
	map:addTile("bridge-wall-ice-right-01", 9, 2)
	map:addTile("tile-background-ice-07", 9, 3)
	map:addTile("tile-background-ice-02", 10, 0)
	map:addTile("tile-background-ice-02", 10, 1)
	map:addTile("tile-ground-ledge-ice-left-01", 10, 2)
	map:addTile("tile-background-ice-06", 10, 3)
	map:addTile("tile-background-ice-cave-art-02", 11, 0)
	map:addTile("tile-background-ice-06", 11, 1)
	map:addTile("tile-ground-ice-big-01", 11, 2)
	map:addTile("tile-background-ice-cave-art-02", 12, 0)
	map:addTile("tile-background-ice-02", 12, 1)
	map:addTile("tile-background-ice-08", 13, 0)
	map:addTile("tile-background-ice-06", 13, 1)
	map:addTile("tile-ground-ice-big-01", 13, 2)
	map:addTile("tile-background-ice-07", 14, 0)
	map:addTile("tile-background-ice-06", 14, 1)

	map:addEmitter("item-package-ice", 6, 1, 1, 0, "")

	map:setSetting("width", "15")
	map:setSetting("height", "4")
	map:setSetting("fishnpc", "false")
	map:setSetting("flyingnpc", "false")
	map:setSetting("gravity", "9.81")
	map:setSetting("packagetransfercount", "1")
	map:addStartPosition("0", "0")
	map:setSetting("points", "100")
	map:setSetting("referencetime", "30")
	map:setSetting("theme", "ice")
	map:setSetting("waterchangespeed", "0")
	map:setSetting("waterfallingdelay", "0")
	map:setSetting("waterheight", "1")
	map:setSetting("waterrisingdelay", "0")
	map:setSetting("wind", "0.0")
end
