/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: player_cmds.inc
	Date: 28.07.2022
	Modified: 31.07.2022
*/

#if !defined _PLAYER_CMDS_
#define _PLAYER_CMDS_

CMD:me(playerid, params[]) {
	new str[512];
	
	if(sscanf(params, "s[512]", str)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /me [Akcja]");
	}
	
	format(str, sizeof(str), "{BA55D3}** %s %s", pVars[playerid][pCharName], str);
	sendDistanceMessage(playerid, 30.0, str, COLOR_WHITE);
	return 1;
}

CMD:do(playerid, params[]) {
	new str[512];
	
	if(sscanf(params, "s[512]", str)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /do [Akcja]");
	}
	
	format(str, sizeof(str), "{9370DB}** %s (( %s ))", str, pVars[playerid][pCharName]);
	sendDistanceMessage(playerid, 30.0, str, COLOR_WHITE);
	return 1;
}

CMD:login(playerid, params[]) {
	TogglePlayerSpectating(playerid, 1);
	
	usedCmdLogin[playerid] = true;
	
	savePlayerValues(playerid);
	setPlayerDefaultValues(playerid);
	
	mainStr[0] = EOS;
	
	format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund� powsta�ym serwerze RolePlay!\n\n{CDC9C9}Posta� o nicku {FFFFFF}%s {CDC9C9}ju� istnieje.\n1.\tJest Twoja? Wpisz has�o i zaloguj si�.\n2.\tChcesz za�o�y� posta�? Kliknij {FFFFFF}STW�RZ{CDC9C9}!", pVars[playerid][pCharName]);
	ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STW�RZ");	
	return 1;
}

CMD:stats(playerid, params[]) {
	new tmpStr[128];
	
	mainStr[0] = EOS;
	
	format(tmpStr, sizeof(tmpStr), "%s (UID %d, ID %d, GUID %d) [%s]", pVars[playerid][pCharName], pVars[playerid][pUid], playerid, pVars[playerid][pGuid], pVars[playerid][pIp]);
	format(mainStr, sizeof(mainStr), "Czas gry:\t\t\t%dh %dm\nAJ:\t\t\t\t%d\nBW:\t\t\t\t%d\nHP:\t\t\t\t%0.1f\nDolary:\t\t\t\t$%d\nBank:\t\t\t\t$%d\nSkin:\t\t\t\t%d", 
	pVars[playerid][pHours], pVars[playerid][pMinutes], pVars[playerid][pAj], pVars[playerid][pBw], pVars[playerid][pHp], pVars[playerid][pMoney], pVars[playerid][pBank], pVars[playerid][pSkin]);
	ShowPlayerDialog(playerid, DIALOG_STATS, DIALOG_STYLE_LIST, tmpStr, mainStr, "OK", "Zamknij");
	return 1;
}

CMD:adminduty(playerid, params[]) {
	if(pVars[playerid][pAccRank] < SUPPORT_RANK && pVars[playerid][pAccRank] < HEADADMIN_RANK) {
		return 1;
	}
	
	if(!pVars[playerid][pIsAdminDuty]) {
		pVars[playerid][pIsAdminDuty] = true;
			
		SendClientMessage(playerid, COLOR_WHITE, "{00FF00}[Admin]{00FF00}: Admin Duty w��czone!");
	} else {
		pVars[playerid][pIsAdminDuty] = false;
			
		SendClientMessage(playerid, COLOR_WHITE, "{00FF00}[Admin]{00FF00}: Admin Duty wy��czone!");
	}
	return 1;
}

CMD:givehealth(playerid, params[]) {
	if(pVars[playerid][pIsAdminDuty]) {
		new toPlayerid, hp; // id player to give hp
		
		mainStr[0] = EOS;
		
		if(sscanf(params, "ii", toPlayerid, hp)) {
			return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[CMD]{FFFFFF}: Poprawnie u�ycie komendy to /givehealth [Id gracza][ilo�� zdrowia].");
		}
		
		pVars[toPlayerid][pHp] = hp;
		SetPlayerHealth(toPlayerid, pVars[toPlayerid][pHp]);
		
		format(mainStr, sizeof(mainStr), "{00FF00}[Admin]{00FF00}: Otrzymales zdrowie od admina %s", pVars[playerid][pAccName]);
		SendClientMessage(toPlayerid, COLOR_WHITE, mainStr);
		format(mainStr, sizeof(mainStr), "{00FF00}[Admin]:{00FF00}: Dales zdrowie graczowi %s", pVars[toPlayerid][pCharName2]);
		SendClientMessage(playerid, COLOR_WHITE, mainStr);
	}
	return 1;
}

CMD:freezeplayer(playerid, params[]) {
	if(pVars[playerid][pAccRank] >= SUPPORT_RANK && pVars[playerid][pAccRank] <= HEADADMIN_RANK) {
		new toPlayerid, freezeOnOff;
		
		mainStr[0] = EOS;
		
		if(sscanf(params, "ii", toPlayerid, freezeOnOff)) {	//freezeOnOff: 0-uncontrollable/1-controllable
			return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[CMD]{FFFFFF}: Poprawne u�ycie komendy /freezeplayer [Id gracza][0/1].");
		}
		
		switch(freezeOnOff) {
			case 0: {
				TogglePlayerControllable(toPlayerid, freezeOnOff);
				
				format(mainStr, sizeof(mainStr), "{00FF00}[Admin]{FFFFFF}: Zosta�e� zamro�ony przez admina %s.", pVars[playerid][pAccName]);
				SendClientMessage(toPlayerid, COLOR_WHITE, mainStr);
				format(mainStr, sizeof(mainStr), "{00FF00}[Admin]{FFFFFF}: Zamro�i�e� gracza %s.", pVars[toPlayerid][pCharName2]);
				SendClientMessage(playerid, COLOR_WHITE, mainStr);
			}
			case 1: {
				TogglePlayerControllable(toPlayerid, freezeOnOff);
				
				format(mainStr, sizeof(mainStr), "{00FF00}[Admin]{FFFFFF}: Zosta�e� odmro�ony przez admina %s.", pVars[playerid][pAccName]);
				SendClientMessage(toPlayerid, COLOR_WHITE, mainStr);
				format(mainStr, sizeof(mainStr), "{00FF00}[Admin]{FFFFFF}: Odmro�i�e� gracza %s.", pVars[toPlayerid][pCharName2]);
				SendClientMessage(playerid, COLOR_WHITE, mainStr);
			}
		}
	}
	return 1;
}

CMD:godmode(playerid)
{
	if(pVars[playerid][pAccRank] >= SUPPORT_RANK && pVars[playerid][pAccRank] <= HEADADMIN_RANK)
	{
		if(pVars[playerid][pIsAdminDuty] == true)
		{
			if(!pVars[playerid][pIsGodMode])
			{
				pVars[playerid][pIsGodMode] = true;
				GetPlayerHealth(playerid, pVars[playerid][pHp]);
				SetPlayerHealth(playerid, 999999);
				SendClientMessage(playerid, 0xFFFFFF, "{00FF00}[Admin]{FFFFFF}: W��czono godmode.");
				return 1;
			}
			else
			{
				pVars[playerid][pIsGodMode] = false;
				SetPlayerHealth(playerid, pVars[playerid][pHp]);
				SendClientMessage(playerid, 0xFFFFFF, "{FF0000}[Admin]{FFFFFF}: Wy��czono godmode.");
				return 1;
			}
		}
		else
		{
			return 1;
		}
	
		return 1;
	}
	return 1;
}

CMD:giveweapon(playerid, params[])
{
	if(pVars[playerid][pAccRank] >= SUPPORT_RANK && pVars[playerid][pAccRank] <= HEADADMIN_RANK)
	{
		if(pVars[playerid][pIsAdminDuty])
		{
			new weaponId, ammo;
			if(sscanf(params, "ii", weaponId, ammo))
			{
				SendClientMessage(playerid, 0xFFFFFF, "{FF0000}[CMD]{FFFFFF}: Poprawne u�ycie komendy /giveweapon [Id broni][ilosc amunicji].");
				return 1;
			}
			
			GivePlayerWeapon(playerid, weaponId, ammo);
			SendClientMessage(playerid, 0xFFFFFF, "{00FF00}[Admin]{FFFFFF}: Otrzymano bro�.");
		}
		else
		{
			return 1;
		}
		
	}
	return 1;
}

CMD:spawnvehicle(playerid, params[])
{
	if(pVars[playerid][pAccRank] >= SUPPORT_RANK && pVars[playerid][pAccRank] <= HEADADMIN_RANK)
	{
		if(pVars[playerid][pIsAdminDuty])
		{
			new vehicleId, vehicleModelId;
			if(sscanf(params, "i", vehicleModelId))
			{
				
				return SendClientMessage(playerid, 0xFFFFFF, "{FF0000}[CMD]{FFFFFF}: Poprawne u�ycie komendy /spawnvehicle [model pojazdu].";
			}
			
			GetPlayerPos(playerid, pVars[playerid][pX], pVars[playerid][pY], pVars[playerid][pZ]);
			
			vehicleId = CreateVehicle(vehicleModelId, pVars[playerid][pX] + 1.0, pVars[playerid][pY], pVars[playerid][pZ], 0, -1, -1, -1);
			
			return 1;
		}
		
		return 1;
	}
	return 1;
}