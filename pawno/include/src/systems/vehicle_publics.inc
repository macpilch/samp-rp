/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: vehicle_publics.inc
	Date: 29.07.2022
	Modified: 04.12.2022
*/

#if !defined _VEHICLE_PUBLICS_
#define _VEHICLE_PUBLICS_

sampCallback:OnPlayerEnterVehicle(playerid, vehicleid, ispassenger) {
	if(vehicleid && isVehicleInUse(vehicleid) && pVars[playerid][pDriverLicense] < 1) {
		ClearAnimations(playerid);
		
		SendClientMessage(playerid, COLOR_WHITE, "(!) Pami�taj, to RolePlay. Sw�j pojazd musisz kupi� lub wypo�yczy�.");
		SendClientMessage(playerid, COLOR_WHITE, "(!) Warto znale�� prac�, aby zdoby� pieni�dze na zakup w�asnego pojazdu.");
		SendClientMessage(playerid, COLOR_WHITE, "(!) Zanim b�dzie Ci� sta�, u�yj /budka, by dzwoni� po taxi, lub /bus. Prowadzi� mo�na po przegraniu 10min.");
	}
	
	if(vehicleid && !vehicleNonEngine(vehicleid) && pVars[playerid][pDriverLicense] < 1 && !drivingCourse[playerid] && !ispassenger) {
		ClearAnimations(playerid);
		
		mainStr[0] = EOS;
		strcat(mainStr, "Musisz najpierw wyrobi� prawo jazdy.\nDo tego czasu u�yj budek, by dzwoni� po taks�wki, lub /bus.\n\n");
		strcat(mainStr, "By wyrobi� prawko, kup telefon i zadzwo� do nauki jazdy pod numerem 333.");
		ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
	}
	return 1;
}

sampCallback:OnPlayerExitVehicle(playerid, vehicleid) {
	SendClientMessage(playerid, COLOR_WHITE, "Witma ! OnPlayerExitVehicle");
	return 1;
}

sampCallback:OnVehicleSpawn(vehicleid) {
	
	return 1;
}

sampCallback:OnVehicleDeath(vehicleid, killerid) {
	SendClientMessage(killerid, COLOR_WHITE, "Witma ! OnVehicleDeath");
	
	new vehid = actualVehicle[killerid];
	
	DestroyVehicle(vehicleid);
	vVars[vehid][vSpawned] = false;
	vVars[vehid][vEngine] = false;
	GameTextForPlayer(killerid, "Pojazd zostanie odspawnowany.", 5000, 3);
	return 1;
}

sampCallback:OnVehicleMod(playerid, vehicleid, componentid) {
	SendClientMessage(playerid, COLOR_WHITE, "Witma ! OnVehicleMod");
	return 1;
}

sampCallback:OnVehiclePaintjob(playerid, vehicleid, paintjobid) {
	SendClientMessage(playerid, COLOR_WHITE, "Witma ! OnVehiclePaintjob");
	return 1;
}

sampCallback:OnVehicleRespray(playerid, vehicleid, color1, color2) {
	SendClientMessage(playerid, COLOR_WHITE, "Witma ! OnVehicleRespray");
	return 1;
}

sampCallback:OnVehicleDamageStatusUpdate(vehicleid, playerid) {
	SendClientMessage(playerid, COLOR_WHITE, "Witma ! OnVehicleDamageStatusUpdate");
	
	new panels, doors, lights, tires;
	new damage = setPlayerVehDamage(playerid);
	
	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	
	if(!hasBelts[playerid]) {
		SetPlayerHealth(playerid, pVars[playerid][pHp] - damage);
	} else {
		SetPlayerHealth(playerid, pVars[playerid][pHp] - (damage + 2));
	}
	
	if(damage >= 4) {
		SetTimerEx("healthDamage", 100, false, "i", playerid);
	}
	return 1;
}

sampCallback:OnVehicleStreamIn(vehicleid, forplayerid) {
	SendClientMessage(forplayerid, COLOR_WHITE, "Witma ! OnVehicleStreamIn");
	return 1;
}

sampCallback:OnVehicleStreamOut(vehicleid, forplayerid) {
	SendClientMessage(forplayerid, COLOR_WHITE, "Witma ! OnVehicleStreamOut");
	return 1;
}

#endif 