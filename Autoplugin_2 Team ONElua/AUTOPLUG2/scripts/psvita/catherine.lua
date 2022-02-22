--Ckecking game Catherine
CatherineTB = {
	{ id = "PCSG01179", region = "Japan" },
}

function Catherine_HD()

	local CATHERINE_ID = "CATHERINEHD.png"

	local patchs = {
		{ res = "Catherine Full Body 1280x720 HD",  desc = LANGUAGE["MENU_PSVITA_INSTALL_CATHERINE_HD_DESC"], path = "catherinefbhd.suprx" },
	}

	for i=1,#patchs do
		for j=1,#plugins do
			if patchs[i].desc == plugins[j].desc then
				patchs[i].res = plugins[j].name
			end
		end
	end

	local scroll,selector,xscroll = newScroll(patchs,#patchs),1,10
	while true do
		buttons.read()
		if change or ReloadConfig then buttons.homepopup(0) else buttons.homepopup(1) end

		if back2 then back2:blit(0,0) end

		draw.offsetgradrect(0,0,960,55,color.blue:a(85),color.blue:a(85),0x0,0x0,20)
		screen.print(480,20,LANGUAGE["INSTALL_CATHERINE_HD_TITLE"],1.2,color.white,0x0,__ACENTER)

		draw.fillrect(0,64,960,322,color.shine:a(25))

		--Games
		local xRoot = 200
		local w = (955-xRoot)/#CatherineTB
		for i=1, #CatherineTB do
			if selector == i then
				draw.fillrect(xRoot,63,w,42, color.green:a(90))
			end
			screen.print(xRoot+(w/2), 75, CatherineTB[i].id, 1, color.white, color.blue, __ACENTER)
			xRoot += w
		end

		local y = 155
		for i=scroll.ini, scroll.lim do

			if i == scroll.sel then draw.offsetgradrect(3,y-10,952,38,color.shine:a(75),color.shine:a(135),0x0,0x0,21) end

			idx = tai.find(CatherineTB[selector].id, patchs[i].path)
			if idx != nil then
				if files.exists(tai.gameid[ CatherineTB[selector].id ].prx[idx].path) then
					if dotg then dotg:blit(924,y-1) else draw.fillrect(924,y-2,21,21,color.green:a(205)) end
				else
					if doty then doty:blit(924,y-1) else draw.fillrect(924,y-2,21,21,color.yellow:a(205)) end
				end
			end

			screen.print(25,y, patchs[i].res)
			y+=45
		end

		--Instructions
		screen.print(25, 245, LANGUAGE["INSTRUCTIONS_HD_PATCH"],1,color.white,color.blue,__ALEFT)

		if patchs[scroll.sel].desc then
			if screen.textwidth(patchs[scroll.sel].desc) > 925 then
				xscroll = screen.print(xscroll, 400, patchs[scroll.sel].desc,1,color.white,color.blue,__SLEFT,935)
			else
				screen.print(480, 400, patchs[scroll.sel].desc,1,color.white,color.blue,__ACENTER)
			end
		end

		if buttonskey then buttonskey:blitsprite(10, 483, saccept) end
        screen.print(40, 485, LANGUAGE["INSTALL_P4G_HD"], 1, color.white, color.black, __ALEFT)

		if buttonskey then buttonskey:blitsprite(10,518,scancel) end
		screen.print(40,522,LANGUAGE["STRING_BACK"],1,color.white,color.black, __ALEFT)

		if buttonskey3 then buttonskey3:blitsprite(920,518,1) end
		screen.print(915,522,LANGUAGE["STRING_CLOSE"],1,color.white,color.blue, __ARIGHT)

		screen.flip()

		--------------------------	Controls	--------------------------

		if buttons.cancel then break end

		--Exit
		if buttons.start then
			exit_bye_bye()
		end

		vol_mp3()

		if scroll.maxim > 0 then

			if buttons.left or buttons.right then xscroll = 10 end

			if buttons.up or buttons.analogly < -60 then
				if scroll:up() then xscroll = 10 end
			end
			if buttons.down or buttons.analogly > 60 then
				if scroll:down() then xscroll = 10 end
			end

			if buttons.accept then
				Patch_Catherine_install(CatherineTB[selector],patchs[scroll.sel])
			end

			if buttons.triangle then

				local vbuff = screen.buffertoimage()

				local onNetGetFileOld = onNetGetFile
				onNetGetFile = nil

				local img = image.load(screenshots..CATHERINE_ID)
				if not img then
					if http.download(string.format("https://raw.githubusercontent.com/%s/%s/master/screenshots/%s", APP_REPO, APP_PROJECT, CATHERINE_ID), screenshots..CATHERINE_ID).success then
						img = image.load(screenshots..CATHERINE_ID)
					end
				end

				onNetGetFile = onNetGetFileOld				
				if img then
					if vbuff then vbuff:blit(0,0) elseif back2 then back2:blit(0,0) end
					img:scale(85)
					img:center()
					img:blit(480,272)
					screen.flip()
					buttons.waitforkey()
				end
				img,vbuff = nil,nil

			end

		end

	end

end


function Patch_Catherine_install(game,res)

	--Copy plugin to tai folder
	files.copy(path_plugins.."catherineHD/"..res.path, path_tai)

	tai.put(game.id, path_tai..res.path)
	ReloadConfig,change = true,true

	if back2 then back2:blit(0,0) end
		message_wait(LANGUAGE["INSTALLING_CATHERINE_HD_PATCH"].."\n\n"..res.res)
	os.delay(850)

end
