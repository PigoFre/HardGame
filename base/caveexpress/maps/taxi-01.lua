function getName()
	return "Taxi 01"
end

function onMapLoaded()
end

function initMap()
	-- get the current map context
	local map = Map.get()
	map:addTile("tile-background-big-01", 0.000000, 0.000000)
	map:addTile("tile-background-01", 0.000000, 2.000000)
	map:addTile("tile-background-01", 0.000000, 3.000000)
	map:addTile("tile-rock-big-01", 0.000000, 4.000000)
	map:addTile("tile-background-01", 0.000000, 6.000000)
	map:addTile("tile-ground-01", 0.000000, 8.000000)
	map:addTile("tile-rock-03", 0.000000, 9.000000)
	map:addTile("tile-rock-slope-right-02", 0.000000, 10.000000)
	map:addTile("tile-background-01", 0.000000, 11.000000)
	map:addTile("tile-background-02", 0.000000, 12.000000)
	map:addTile("tile-background-02", 0.000000, 13.000000)
	map:addTile("tile-rock-big-01", 0.000000, 14.000000)
	map:addTile("tile-background-02", 1.000000, 2.000000)
	map:addTile("tile-background-02", 1.000000, 3.000000)
	map:addTile("tile-background-02", 1.000000, 6.000000)
	map:addTile("tile-background-window-02", 1.000000, 7.000000)
	map:addTile("tile-ground-02", 1.000000, 8.000000)
	map:addTile("tile-rock-slope-right-02", 1.000000, 9.000000)
	map:addTile("tile-background-02", 1.000000, 10.000000)
	map:addTile("tile-background-02", 1.000000, 11.000000)
	map:addTile("tile-background-02", 1.000000, 12.000000)
	map:addTile("tile-background-01", 1.000000, 13.000000)
	map:addTile("tile-background-03", 2.000000, 0.000000)
	map:addTile("tile-background-03", 2.000000, 1.000000)
	map:addTile("tile-background-big-01", 2.000000, 2.000000)
	map:addTile("tile-ground-ledge-right-01", 2.000000, 4.000000)
	map:addTile("tile-background-01", 2.000000, 5.000000)
	map:addTile("tile-background-03", 2.000000, 6.000000)
	map:addTile("tile-background-cave-art-01", 2.000000, 7.000000)
	map:addTile("tile-ground-01", 2.000000, 8.000000)
	map:addTile("tile-background-03", 2.000000, 9.000000)
	map:addTile("liane-01", 2.000000, 9.000000)
	map:addTile("tile-background-03", 2.000000, 10.000000)
	map:addTile("tile-ground-02", 2.000000, 12.000000)
	map:addTile("tile-background-03", 2.000000, 13.000000)
	map:addTile("tile-rock-big-01", 2.000000, 14.000000)
	map:addTile("tile-background-02", 3.000000, 0.000000)
	map:addTile("tile-background-02", 3.000000, 1.000000)
	map:addTile("tile-background-02", 3.000000, 4.000000)
	map:addTile("tile-background-02", 3.000000, 5.000000)
	map:addTile("tile-background-02", 3.000000, 6.000000)
	map:addTile("tile-background-02", 3.000000, 7.000000)
	map:addTile("tile-ground-ledge-right-01", 3.000000, 8.000000)
	map:addTile("tile-background-02", 3.000000, 9.000000)
	map:addTile("tile-background-02", 3.000000, 10.000000)
	map:addTile("tile-background-window-01", 3.000000, 11.000000)
	map:addTile("tile-background-big-01", 3.000000, 12.000000)
	map:addTile("bridge-wall-left-01", 3.000000, 12.000000)
	map:addTile("tile-background-03", 4.000000, 0.000000)
	map:addTile("tile-background-03", 4.000000, 1.000000)
	map:addTile("tile-background-03", 4.000000, 2.000000)
	map:addTile("tile-background-03", 4.000000, 3.000000)
	map:addTile("tile-background-big-01", 4.000000, 4.000000)
	map:addTile("tile-background-03", 4.000000, 6.000000)
	map:addTile("tile-background-01", 4.000000, 7.000000)
	map:addTile("tile-background-04", 4.000000, 8.000000)
	map:addTile("tile-background-01", 4.000000, 9.000000)
	map:addTile("tile-background-03", 4.000000, 10.000000)
	map:addTile("tile-background-03", 4.000000, 11.000000)
	map:addTile("bridge-plank-01", 4.000000, 12.000000)
	map:addTile("tile-rock-big-01", 4.000000, 14.000000)
	map:addTile("tile-background-big-01", 5.000000, 0.000000)
	map:addTile("tile-background-02", 5.000000, 2.000000)
	map:addTile("tile-background-02", 5.000000, 3.000000)
	map:addTile("tile-background-02", 5.000000, 6.000000)
	map:addTile("tile-background-02", 5.000000, 7.000000)
	map:addTile("tile-background-big-01", 5.000000, 8.000000)
	map:addTile("tile-background-02", 5.000000, 10.000000)
	map:addTile("tile-background-02", 5.000000, 11.000000)
	map:addTile("tile-background-02", 5.000000, 12.000000)
	map:addTile("bridge-wall-right-01", 5.000000, 12.000000)
	map:addTile("tile-background-02", 5.000000, 13.000000)
	map:addTile("tile-background-03", 6.000000, 2.000000)
	map:addTile("tile-background-03", 6.000000, 3.000000)
	map:addTile("tile-ground-01", 6.000000, 4.000000)
	map:addTile("tile-background-01", 6.000000, 5.000000)
	map:addTile("tile-background-03", 6.000000, 6.000000)
	map:addTile("tile-background-03", 6.000000, 7.000000)
	map:addTile("tile-background-big-01", 6.000000, 10.000000)
	map:addTile("tile-rock-big-01", 6.000000, 12.000000)
	map:addTile("tile-rock-big-01", 6.000000, 14.000000)
	map:addTile("tile-background-02", 7.000000, 0.000000)
	map:addTile("tile-background-02", 7.000000, 1.000000)
	map:addTile("tile-background-02", 7.000000, 2.000000)
	map:addTile("tile-background-02", 7.000000, 3.000000)
	map:addTile("tile-ground-01", 7.000000, 4.000000)
	map:addTile("tile-background-03", 7.000000, 5.000000)
	map:addTile("liane-01", 7.000000, 5.000000)
	map:addTile("tile-background-02", 7.000000, 6.000000)
	map:addTile("tile-background-02", 7.000000, 7.000000)
	map:addTile("tile-background-02", 7.000000, 8.000000)
	map:addTile("tile-background-02", 7.000000, 9.000000)
	map:addTile("liane-01", 7.500000, 5.000000)
	map:addTile("tile-background-03", 8.000000, 0.000000)
	map:addTile("tile-background-cave-art-01", 8.000000, 1.000000)
	map:addTile("tile-ground-01", 8.000000, 2.000000)
	map:addTile("tile-rock-big-01", 8.000000, 3.000000)
	map:addTile("tile-rock-03", 8.000000, 5.000000)
	map:addTile("tile-rock-01", 8.000000, 6.000000)
	map:addTile("tile-rock-slope-left-02", 8.000000, 7.000000)
	map:addTile("tile-background-big-01", 8.000000, 8.000000)
	map:addTile("tile-background-03", 8.000000, 10.000000)
	map:addTile("tile-background-01", 8.000000, 11.000000)
	map:addTile("tile-rock-big-01", 8.000000, 12.000000)
	map:addTile("tile-rock-big-01", 8.000000, 14.000000)
	map:addTile("tile-background-cave-art-01", 9.000000, 0.000000)
	map:addTile("tile-background-window-02", 9.000000, 1.000000)
	map:addTile("tile-ground-02", 9.000000, 2.000000)
	map:addTile("tile-rock-big-01", 9.000000, 5.000000)
	map:addTile("tile-rock-02", 9.000000, 7.000000)
	map:addTile("liane-01", 9.000000, 8.000000)
	map:addTile("tile-background-02", 9.000000, 10.000000)
	map:addTile("tile-background-02", 9.000000, 11.000000)
	map:addTile("tile-background-04", 10.000000, 0.000000)
	map:addTile("tile-ground-03", 10.000000, 2.000000)
	map:addTile("tile-rock-03", 10.000000, 3.000000)
	map:addTile("tile-rock-01", 10.000000, 4.000000)
	map:addTile("tile-rock-slope-right-02", 10.000000, 7.000000)
	map:addTile("tile-background-03", 10.000000, 8.000000)
	map:addTile("tile-background-03", 10.000000, 9.000000)
	map:addTile("tile-background-03", 10.000000, 10.000000)
	map:addTile("tile-ground-01", 10.000000, 11.000000)
	map:addTile("tile-rock-big-01", 10.000000, 12.000000)
	map:addTile("tile-rock-big-01", 10.000000, 14.000000)
	map:addTile("tile-background-02", 11.000000, 0.000000)
	map:addTile("tile-background-cave-art-01", 11.000000, 1.000000)
	map:addTile("tile-ground-01", 11.000000, 2.000000)
	map:addTile("tile-rock-slope-right-02", 11.000000, 3.000000)
	map:addTile("tile-background-02", 11.000000, 4.000000)
	map:addTile("tile-background-02", 11.000000, 5.000000)
	map:addTile("tile-ground-03", 11.000000, 6.000000)
	map:addTile("tile-background-02", 11.000000, 7.000000)
	map:addTile("tile-background-02", 11.000000, 8.000000)
	map:addTile("tile-background-02", 11.000000, 9.000000)
	map:addTile("tile-background-cave-art-01", 11.000000, 10.000000)
	map:addTile("tile-ground-02", 11.000000, 11.000000)
	map:addTile("tile-background-03", 12.000000, 0.000000)
	map:addTile("tile-background-03", 12.000000, 1.000000)
	map:addTile("tile-ground-ledge-right-01", 12.000000, 2.000000)
	map:addTile("tile-background-03", 12.000000, 3.000000)
	map:addTile("tile-background-03", 12.000000, 4.000000)
	map:addTile("tile-ground-02", 12.000000, 6.000000)
	map:addTile("tile-background-01", 12.000000, 7.000000)
	map:addTile("tile-background-03", 12.000000, 8.000000)
	map:addTile("tile-background-03", 12.000000, 9.000000)
	map:addTile("tile-background-window-02", 12.000000, 10.000000)
	map:addTile("tile-ground-03", 12.000000, 11.000000)
	map:addTile("tile-rock-big-01", 12.000000, 12.000000)
	map:addTile("tile-rock-big-01", 12.000000, 14.000000)
	map:addTile("tile-background-02", 13.000000, 0.000000)
	map:addTile("tile-background-02", 13.000000, 1.000000)
	map:addTile("tile-background-02", 13.000000, 2.000000)
	map:addTile("tile-background-02", 13.000000, 3.000000)
	map:addTile("tile-background-02", 13.000000, 4.000000)
	map:addTile("tile-background-window-01", 13.000000, 5.000000)
	map:addTile("tile-ground-05", 13.000000, 6.000000)
	map:addTile("tile-background-big-01", 13.000000, 7.000000)
	map:addTile("tile-background-02", 13.000000, 9.000000)
	map:addTile("tile-ground-03", 13.000000, 11.000000)
	map:addTile("tile-background-03", 14.000000, 0.000000)
	map:addTile("tile-background-03", 14.000000, 1.000000)
	map:addTile("tile-background-03", 14.000000, 2.000000)
	map:addTile("tile-background-03", 14.000000, 3.000000)
	map:addTile("tile-background-03", 14.000000, 4.000000)
	map:addTile("tile-background-big-01", 14.000000, 5.000000)
	map:addTile("tile-background-big-01", 14.000000, 9.000000)
	map:addTile("tile-ground-02", 14.000000, 11.000000)
	map:addTile("tile-rock-big-01", 14.000000, 12.000000)
	map:addTile("tile-rock-big-01", 14.000000, 14.000000)
	map:addTile("tile-background-02", 15.000000, 0.000000)
	map:addTile("tile-background-02", 15.000000, 1.000000)
	map:addTile("tile-background-02", 15.000000, 2.000000)
	map:addTile("tile-background-02", 15.000000, 3.000000)
	map:addTile("tile-background-02", 15.000000, 4.000000)
	map:addTile("tile-background-02", 15.000000, 7.000000)
	map:addTile("tile-background-02", 15.000000, 8.000000)
	map:addTile("tile-ground-01", 15.000000, 11.000000)
	map:addTile("tile-background-02", 16.000000, 0.000000)
	map:addTile("tile-background-02", 16.000000, 1.000000)
	map:addTile("tile-background-02", 16.000000, 2.000000)
	map:addTile("tile-background-02", 16.000000, 3.000000)
	map:addTile("tile-ground-ledge-left-01", 16.000000, 4.000000)
	map:addTile("tile-background-big-01", 16.000000, 5.000000)
	map:addTile("tile-background-04", 16.000000, 7.000000)
	map:addTile("tile-ground-04", 16.000000, 8.000000)
	map:addTile("tile-rock-big-01", 16.000000, 9.000000)
	map:addTile("tile-ground-01", 16.000000, 11.000000)
	map:addTile("tile-rock-big-01", 16.000000, 12.000000)
	map:addTile("tile-rock-big-01", 16.000000, 14.000000)
	map:addTile("tile-background-02", 17.000000, 0.000000)
	map:addTile("tile-background-02", 17.000000, 1.000000)
	map:addTile("tile-background-02", 17.000000, 2.000000)
	map:addTile("tile-ground-03", 17.000000, 4.000000)
	map:addTile("tile-background-04", 17.000000, 7.000000)
	map:addTile("tile-ground-04", 17.000000, 8.000000)
	map:addTile("tile-ground-01", 17.000000, 11.000000)
	map:addTile("tile-background-02", 18.000000, 0.000000)
	map:addTile("tile-background-02", 18.000000, 1.000000)
	map:addTile("tile-background-02", 18.000000, 2.000000)
	map:addTile("tile-background-02", 18.000000, 3.000000)
	map:addTile("tile-ground-03", 18.000000, 4.000000)
	map:addTile("tile-background-02", 18.000000, 5.000000)
	map:addTile("liane-01", 18.000000, 5.000000)
	map:addTile("tile-background-big-01", 18.000000, 6.000000)
	map:addTile("tile-background-big-01", 18.000000, 8.000000)
	map:addTile("tile-rock-big-01", 18.000000, 10.000000)
	map:addTile("tile-rock-big-01", 18.000000, 12.000000)
	map:addTile("tile-rock-big-01", 18.000000, 14.000000)
	map:addTile("tile-background-02", 19.000000, 0.000000)
	map:addTile("tile-background-02", 19.000000, 1.000000)
	map:addTile("tile-background-02", 19.000000, 2.000000)
	map:addTile("tile-background-02", 19.000000, 3.000000)
	map:addTile("tile-ground-03", 19.000000, 4.000000)
	map:addTile("tile-rock-slope-left-02", 19.000000, 5.000000)

	map:addEmitter("tree", 0.000000, 2.000000, 1, 0, "right=false")
	map:addEmitter("tree", 6.000000, 10.000000, 1, 0, "right=false")
	map:addEmitter("item-stone", 16.000000, 7.000000, 1, 0, "right=false")

	map:addCave("tile-cave-01", 0.000000, 7.000000, "npc-woman", 5000)
	map:addCave("tile-cave-02", 2.000000, 11.000000, "", 5000)
	map:addCave("tile-cave-01", 10.000000, 1.000000)
	map:addCave("tile-cave-02", 12.000000, 5.000000, "npc-grandpa", 5000)
	map:addCave("tile-cave-02", 13.000000, 10.000000, "npc-man", 5000)
	map:addCave("tile-cave-01", 17.000000, 3.000000, "npc-woman", 5000)

	map:setSetting("width", "20")
	map:setSetting("height", "16")
	map:setSetting("fishnpc", "false")
	map:setSetting("flyingnpc", "false")
	map:setSetting("gravity", "9.81")
	map:setSetting("npcs", "3")
	map:setSetting("npctransfercount", "2")
	map:setSetting("packagetransfercount", "0")
	map:setSetting("points", "100")
	map:setSetting("referencetime", "30")
	map:setSetting("sideborderfail", "false")
	map:setSetting("waterchangespeed", "0.000000")
	map:setSetting("waterfallingdelay", "0")
	map:setSetting("waterheight", "3.500000")
	map:setSetting("waterrising", "0.0")
	map:setSetting("waterrisingdelay", "0")
	map:setSetting("wind", "0")

	map:addStartPosition("6.000000", "3.000000")
end
