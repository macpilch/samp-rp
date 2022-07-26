/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: player_cmds.inc
	Date: 28.07.2022
	Modified: 04.12.2022
*/

#if !defined _PLAYER_CMDS_
#define _PLAYER_CMDS_

CMD:help(playerid, params[]) {
	mainStr[0] = EOS;
	strcat(mainStr, "{FFFFFF}0\tJak zacz��?\n0\tPodstawowe komendy\n");
	strcat(mainStr, "0\tBW\n0\tAnimacje\n0\tPojazdy\n0\tPrzedmioty\n");
	strcat(mainStr, "0\tOferty\n0\tPraca\n0\tCzaty grupowe\n--- Pomoc dotycz�ca Twoich grup:");
	ShowPlayerDialog(playerid, DIALOG_HELP, DIALOG_STYLE_LIST, "Pomoc > Wyb�r kategorii pomocy", mainStr, "Wybierz", "Anuluj");
	return 1;
}

CMD:pomoc(playerid, params[]) {
	return pc_cmd_help(playerid, params);
}

CMD:w(playerid, params[]) {
	new pId, pmStr[256];
	
	if(sscanf(params, "is[256]", pId, pmStr)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /w [ID Gracza] [Wiadomo��]");
	}
	
	if(pId == playerid) {
		return GameTextForPlayer(playerid, "~y~Nie mozesz wyslac wiadomosci do siebie.", 5000, 3);
	}
	
	if(!IsPlayerConnected(pId)) {
		return GameTextForPlayer(playerid, "~r~Taki gracz nie istnieje.", 5000, 3);
	}
	
	if(!chatMessages[pId][0]) {
		return SendClientMessage(playerid, COLOR_GRAY, "Ten gracz ma wy��czone wiadomo�ci.");
	}
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "(( > %s (%d): %s ))", pVars[pId][pCharName], pId, pmStr);
	SendClientMessage(playerid, COLOR_LIGHTORANGE, mainStr);
	format(mainStr, sizeof(mainStr), "(( %s (%d): %s ))", pVars[playerid][pCharName], playerid, pmStr);
	SendClientMessage(pId, COLOR_ORANGE, mainStr);
	return 1;
}

CMD:czat(playerid, params[]) {
	new pId;
	
	if(sscanf(params, "i", pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /czat [ID Gracza]");
	}
	
	SendClientMessage(playerid, COLOR_WHITE, "{FFFF00}Czat z graczem uruchomiony. Od teraz zamiast u�ywa� /w [Gracz], po prostu zacznij pisa�.");
	SendClientMessage(playerid, COLOR_WHITE, "{FFFF00}Aby anulowa� czat, po prostu wpisz /czat.");
	return 1;
}

CMD:tog(playerid, params[]) {
	new opt[8];
	
	if(sscanf(params, "s[8]", opt)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /tog [w]");
	}
	
	if(strfind(opt, "w", true) != 1) {
		GameTextForPlayer(playerid, "~w~Kanaly grupowe ~r~~n~wylaczone", 5000, 6);
	}
	return 1;
}

CMD:pokaz(playerid, params[]) {
	new pId, opt[16];
	
	if(sscanf(params, "s[16]i", opt, pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /pokaz [przedmioty/dowod/prawko/id] [ID Gracza]");
	}
	
	if(!IsPlayerConnected(pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Nie odnaleziono takiego gracza.");
	}
	return 1;
}

CMD:podaj(playerid, params[]) {
	if(!isPlayerDuty[playerid]) {
		return SendClientMessage(playerid, COLOR_GRAY, "U�yj /duty, aby wej�� na s�u�b� grupy, z kt�rej chcesz co� poda�.");
	}
	return 1;
}

CMD:blokada(playerid, params[]) {
	new type;
	
	if(sscanf(params, "i", type)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /blokada [1-5]");
	}
	return 1;
}

CMD:c(playerid, params[]) {
	new str[256];
	
	if(sscanf(params, "s[256]", str)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /c [Tekst]");
	}
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "%s szepcze: %s", pVars[playerid][pCharName], str);
	sendDistanceMessage(playerid, 10.0, mainStr, COLOR_WHITE, COLOR_GRAY, COLOR_MEDGRAY, COLOR_DARKGRAY);
	return 1;
}

CMD:m(playerid, params[]) {
	new str[256];
	
	if(sscanf(params, "s[256]", str)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /m [Tekst]");
	}
	
	format(str, sizeof(str), "{FFFF00}%s :o< %s", pVars[playerid][pCharName], str);
	sendDistanceMessage(playerid, 100.0, str, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
	return 1;
}

CMD:a(playerid, params[]) {
	new adminsCount; // debug
	
	mainStr[0] = EOS;
	
	foreach(new i : Player) {
		if(pVars[i][pRank] >= SUPPORT_RANK && pVars[i][pRank] <= HEADADMIN_RANK) {
			if(isAdminDuty[i]) {
				adminsCount++;
				
				if(adminsCount > 0) {
					format(mainStr, sizeof(mainStr), "%sADM %d\t\t\t\t%s\n", mainStr, pVars[i][pRank], pVars[i][pAccName]);
				}
			} else {
				adminsCount = 0;
			}
		}
	}
	
	if(!adminsCount) {
		return GameTextForPlayer(playerid, "~r~Nie znaleziono ~w~graczy~n~~r~Spelniajacych kryteria.", 5000, 3);
	}
	
	ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Lista graczy", mainStr, "OK", "Zamknij");
	return 1;
}

CMD:id(playerid, params[]) {
	new name[24], str[128];
	
	if(sscanf(params, "s[24]", name)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /id [Cz�� Imienia]");
	}
	
	foreach(new i : Player) {
		if(strfind(pVars[i][pCharName], name, true) != -1) {
			format(str, sizeof(str), "%s\n{FFFFFF}%d\t%s", str, i, pVars[i][pCharName]);
		} else {
			return GameTextForPlayer(playerid, "~r~Brak wynikow~n~~n~~w~Zaden gracz nie spelnia~n~kryteriow wyszukiwan.", 4000, 3);
		}
	}
	
	ShowPlayerDialog(playerid, DIALOG_SEARCH_ID, DIALOG_STYLE_LIST, "Lista graczy", str, "PW", "Zamknij");
	return 1;
}

CMD:sprobuj(playerid, params[]) {
	new action[128], str[256];
	new randCase;
	new actionCases[][] = {
		"odni�s� sukces pr�buj�c",
		"odni�s� pora�k� pr�buj�c"
	};
	
	if(sscanf(params, "s[128]", action)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /sprobuj [Akcja]");
	}
	
	randCase = random(sizeof(actionCases));
	
	format(str, sizeof(str), "*** %s %s %s.", pVars[playerid][pCharName], actionCases[randCase], action);
	sendDistanceMessage(playerid, 30.0, str, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	return 1;
}

CMD:me(playerid, params[]) {
	new str[512], str2[128];
	new randomTips[][] = {
		"[Akcja] - komenda s�u�y do opisywania OBSERWOWALNYCH czynno�ci postaci.",
		"wyci�ga kluczyki - poprawne u�ycie komendy.",
		"szuka pracy - NIEPOPRAWNE u�ycie komendy (tego nie da si� zaobserwowa� na pierwszy rzut oka)."
	};
	
	if(sscanf(params, "s[512]", str)) {
		for(new i = 0; i < sizeof(randomTips); i++) {
			format(str2, sizeof(str2), "Tip: /me %s", randomTips[i]);
			SendClientMessage(playerid, COLOR_GRAY, str2);
		}
		return 1;
	}
	
	format(str, sizeof(str), "{8D8098}** %s %s", pVars[playerid][pCharName], str);
	sendDistanceMessage(playerid, 30.0, str, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
	return 1;
}

CMD:ja(playerid, params[]) {
	return pc_cmd_me(playerid, params);
}

CMD:do(playerid, params[]) {
	new str[512];
	
	if(sscanf(params, "s[512]", str)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /do [Akcja]");
	}
	
	format(str, sizeof(str), "{666287}** %s (( %s ))", str, pVars[playerid][pCharName]);
	sendDistanceMessage(playerid, 30.0, str, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
	return 1;
}

CMD:pay(playerid, params[]) {
	new pId, money;
	new str[128];
	
	if(sscanf(params, "ii", pId, money)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /pay [ID/nazwa gracza] [Ilo�� pieni�dzy] | Przyk�ad: /plac Joe Blow 10");
	}
	
	GivePlayerMoneyEx(playerid, -money);
	GivePlayerMoneyEx(pId, money);
	
	format(str, sizeof(str), "Podano %s $%d. Pami�taj, by p�aci� w Dolarach, u�yj /pay [Gracz] [Ilo��].", pVars[pId][pCharName], money);
	SendClientMessage(playerid, COLOR_WHITE, str);
	format(str, sizeof(str), "Otrzymujesz $%d od %s.", money, pVars[playerid][pCharName]);
	SendClientMessage(pId, COLOR_WHITE, str);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s podaje troch� got�wki %s.", pVars[playerid][pCharName], pVars[pId][pCharName]);
	sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	return 1;
}

CMD:login(playerid, params[]) {
	if(usedCmdLogin[playerid]) {
		return SendClientMessage(playerid, COLOR_GRAY, "Musisz odczeka� minut� od zalogowania, aby si� wylogowa�.");
	}
	
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER) {
		return SendClientMessage(playerid, COLOR_GRAY, "Musisz by� pieszo, by si� wylogowa�.");
	}
	
	TogglePlayerSpectating(playerid, 1);
	SetPlayerName(playerid, pVars[playerid][pAccName]);
	GetPlayerName(playerid, pVars[playerid][pAccName], 24);
	
	hasLoged[playerid] = true;
	usedCmdLogin[playerid] = true;
	
	savePlayerValues(playerid);
	setPlayerDefaultValues(playerid);
	setPlayerCamerasView(playerid);
	SetTimerEx("refreshCmds", 60000, false, "ii", playerid, 0);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "{CD5C5C}Witaj na serverze testowym, przed sekund� powsta�ym serwerze RolePlay!\n\n{CDC9C9}Posta� o nicku {FFFFFF}%s {CDC9C9}ju� istnieje.\n1.\tJest Twoja? Wpisz has�o i zaloguj si�.\n2.\tChcesz za�o�y� posta�? Kliknij {FFFFFF}STW�RZ{CDC9C9}!", pVars[playerid][pCharName]);
	ShowPlayerDialog(playerid, DIALOG_LOGIN_PASS, DIALOG_STYLE_PASSWORD, "Logowanie lub rejestracja", mainStr, "Zaloguj", "STW�RZ");	
	return 1;
}

CMD:stats(playerid, params[]) {
	new tmpStr[128];
	
	mainStr[0] = EOS;
	format(tmpStr, sizeof(tmpStr), "%s (UID %d, ID %d, Globalne %d) [%s]", pVars[playerid][pCharName], pVars[playerid][pUid], playerid, pVars[playerid][pGuid], pVars[playerid][pIp]);
	format(mainStr, sizeof(mainStr), "{FFFFFF}Czas gry:\t\t\t%dh %dm\nAL:\t\t\t\t%d\nAJ:\t\t\t\t%d\nBW:\t\t\t\t%d\nHP:\t\t\t\t%0.1f\nSi�a:\t\t\t\t%d\nP�e�:\t\t\t\t%s\nRz�d:\t\t\t\t%d\nPrawko:\t\t\t%d\nHotel:\t\t\t\t%d\nPrzetrzymanie:\t\t\t%dh\nPDP:\t\t\t\t%d\nPieni�dze:\t\t\t$%d\nBank:\t\t\t\t$%d\nTelefon:\t\t\t%d\nNumer konta:\t\t\t%d\nGrupy:\t\t\t\t%s\nSkin:\t\t\t\t%d\nWyje�d�one:\t\t\t%0.1fkm\nOstatni skin:\t\t\t%d\nDrzwi:\t\t\t\t%d\nZaproszenie od:\t\t%d\n------\n", 
	pVars[playerid][pHours], pVars[playerid][pMinutes], pVars[playerid][pAl], pVars[playerid][pAj], pVars[playerid][pBw] / 60, pVars[playerid][pHp], pVars[playerid][pStrength], pVars[playerid][pSex] ? ("K") : ("M"), pVars[playerid][pGov], pVars[playerid][pDriverLicense], pVars[playerid][pHotel], pVars[playerid][pDetention], pVars[playerid][pPdp], pVars[playerid][pMoney], pVars[playerid][pBank], pVars[playerid][pTelNum], pVars[playerid][pBankAcc], pVars[playerid][pGroup], pVars[playerid][pSkin],
	pVars[playerid][pTraveled], pVars[playerid][pLastSkin], pVars[playerid][pDoors], pVars[playerid][pInvi]);
	ShowPlayerDialog(playerid, DIALOG_STATS, DIALOG_STYLE_LIST, tmpStr, mainStr, "OK", "Zamknij");
	return 1;
}

CMD:opis(playerid, params[]) {
	new str[128];
	
	if(sscanf(params, "s[128]", str)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /opis [Tresc] lub /opis usun");
	}
	
	if(strfind(str, "usun", true) != -1) {
		queryStr[0] = EOS;
		
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
			if(!strlen(str)) {
				return SendClientMessage(playerid, COLOR_GRAY, "Nie masz �adnego opisu.");
			} else {
				format(queryStr, sizeof(queryStr), "UPDATE `Players` SET `Desc` = '\0' WHERE `UID` = '%d'", pVars[playerid][pUid]);
				mysql_query(queryStr);
				
				UpdateDynamic3DTextLabelText(pVars[playerid][pCharDesc], COLOR_WHITE, NULL);
			}
		} else {
			new vehid = actualVehicle[playerid];
			
			format(queryStr, sizeof(queryStr), "UPDATE `Vehicles` SET `Desc` = '\0' WHERE `UID` = '%d'", vVars[vehid][vUid]);
			mysql_query(queryStr);
			
			UpdateDynamic3DTextLabelText(vVars[vehid][vDesc], COLOR_WHITE, NULL);
		}
		
		GameTextForPlayer(playerid, "~w~Opis zostal usuniety.", 4000, 3);
	} else {
		mainStr[0] = EOS;
		queryStr[0] = EOS;
		
		format(queryStr, sizeof(queryStr), "UPDATE `Players` SET `Desc` = '%s' WHERE `UID` = '%d'", str, pVars[playerid][pUid]);
		mysql_query(queryStr);
		
		format(mainStr, sizeof(mainStr), "%s", str);
		SendClientMessage(playerid, COLOR_GRAY, "Opis postaci ustawiony (aby go usun��, wpisz /opis usun):");
		SendClientMessage(playerid, COLOR_PURPLE, mainStr);
		UpdateDynamic3DTextLabelText(pVars[playerid][pCharDesc], COLOR_PURPLE, str);
	}
	return 1;
}

CMD:p(playerid, params[]) {
	showDialogItems(playerid);
	return 1;
}

CMD:u(playerid, params[]) {
	return pc_cmd_p(playerid, params);
}

CMD:o(playerid, params[]) {
	new type[16], pId, cmdParams;
	
	if(sscanf(params, "s[16]ii", type, pId, cmdParams)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /o [Us�uga] [Gracz] (Opcjonalne parametry)");
	}
	
	if(strfind(type, "grupa", true) != -1) {
		mainStr[0] = EOS;
		offerParams[playerid] = cmdParams;
		
		strcat(mainStr, "Wpisz nazw� grupy do, kt�rej chcesz zaprosi� gracza:");
		ShowPlayerDialog(playerid, DIALOG_OFFER_FRACTION_INVITE, DIALOG_STYLE_INPUT, "Grupa", mainStr, "OK", "Anuluj");
	} else if(strfind(type, "kurs", true) != -1) {
		new tmpFracId = checkFractionSrvIdForPlayer(playerid);
		
		if(fVars[tmpFracId][fType] == F_DRVRLIC) {
			sendOfferToPlayer(playerid, pId, cmdParams, 1);
		}
	} else if(strfind(type, "dowod", true) != -1) {
		new tmpFracId = checkFractionSrvIdForPlayer(playerid);
		
		if(fVars[tmpFracId][fType] == F_PUBLIC) {
			sendOfferToPlayer(playerid, pId, cmdParams, 2);
		}
	} else if(strfind(type, "prawko", true) != -1) {
		new tmpFracId = checkFractionSrvIdForPlayer(playerid);
		
		if(pVars[pId][pTraveled] < 5.0) {
			return GameTextForPlayer(playerid, "~r~Ten gracz nie ukonczyl kursu.", 5000, 3);
		}
		
		if(fVars[tmpFracId][fType] == F_PUBLIC) {
			sendOfferToPlayer(playerid, pId, cmdParams, 3);
		}
	} else if(strfind(type, "podatek", true) != -1) {
		new tmpFracId = checkFractionSrvIdForPlayer(playerid);
		
		if(fVars[tmpFracId][fType] == F_PUBLIC) {
			sendOfferToPlayer(playerid, pId, cmdParams, 4);
		}		
	}
	return 1;
}

CMD:time(playerid, params[]) {
	new hours, minutes, seconds;
	new str[32];
	
	gettime(hours, minutes, seconds);
	ApplyAnimation(playerid, "PLAYIDLES", "TIME", 4.1, 0, 1, 1, 1, 1, 1);
	
	format(str, sizeof(str), "~w~godzina: ~p~%02d:%02d:%02d~w~.", hours, minutes, seconds);
	GameTextForPlayer(playerid, str, 7000, 1);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s spogl�da na zegarek.", pVars[playerid][pCharName]);
	sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	return 1;
}

CMD:zegarek(playerid, params[]) {
	return pc_cmd_time(playerid, params);
}

CMD:v(playerid, params[]) {
	if(!checkPlayerVehicleId(playerid)) {
		mainStr[0] = EOS;
		strcat(mainStr, "W tym miejscu pojawi si� lista posiadanych przez Ciebie pojazd�w.\n\n");
		strcat(mainStr, "Kup nowy pojazd w salonie samochodowym lub u�ywany od innego gracza.\n\n");
		strcat(mainStr, "Pojazdom mo�na dodawa� komponenty i zabezpieczenia w warsztatach.");
		return ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
	}
	
	new opt[32];
	
	if(sscanf(params, "s[32]", opt)) {
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
			queryStr[0] = EOS;
			mainStr[0] = EOS;
			
			format(queryStr, sizeof(queryStr), "SELECT `UID`, `ModelID`, `Spawned` FROM `Vehicles` WHERE `CharName` = '%s'", pVars[playerid][pCharName]);
			mysql_query(queryStr);
			mysql_store_result();
			
			enum Values {
				UID = 0,
				ModelID,
				Spawned
			};
			
			new tmpVVars[MAX_VEHICLES][Values];
			new i;
			
			while(mysql_fetch_row(queryStr, "|")) {
				sscanf(queryStr, "p<|>iii", tmpVVars[i][UID], tmpVVars[i][ModelID], tmpVVars[i][Spawned]);
				
				if(tmpVVars[i][Spawned]) {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d   %s*", mainStr, tmpVVars[i][UID], VehicleNames[tmpVVars[i][ModelID] - 400]);
				} else {
					format(mainStr, sizeof(mainStr), "%s\n{FFFFFF}%d   %s", mainStr, tmpVVars[i][UID], VehicleNames[tmpVVars[i][ModelID] - 400]);
				}
				
				i++;
			}
			
			mysql_free_result();
			ShowPlayerDialog(playerid, DIALOG_VEHICLE_SELECT, DIALOG_STYLE_LIST, "Wyb�r pojazdu (* = zespawnowany)", mainStr, "(Un)spawn", "Anuluj");
		} else {
			mainStr[0] = EOS;
			strcat(mainStr, "{FFFFFF}1\tW��cz/wy��cz �wiat�a\n2\tOtw�rz/zamknij mask�\n3\tOtw�rz/zamknij baga�nik\n");
			strcat(mainStr, "4\tOtw�rz/zamknij okno\n5\tZobacz komponenty pojazdu\n6\tUstaw unikaln� rejestracj�\n-\n");
			strcat(mainStr, "7\tPrzypisz pod grup�\n8\tUstaw jako pojazd specjalny (dla grup)\n9\tSprzedaj pojazd graczowi...\n");
			strcat(mainStr, "10\tWymie� si� pojazdem z graczem...");
			ShowPlayerDialog(playerid, DIALOG_VEHICLE_OPTIONS, DIALOG_STYLE_LIST, "W poje�dzie", mainStr, "OK", "Anuluj");
		}
	} else {
		if(strfind(opt, "zaparkuj", true) != -1 || strfind(opt, "parkuj", true) != -1) {
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				new vehid = actualVehicle[playerid];
				new Float:x, Float:y, Float:z;
				
				GetVehiclePos(vVars[vehid][vId], x, y, z);
				format(queryStr, sizeof(queryStr), "UPDATE `Vehicles` SET `X` = '%f', `Y` = '%f', `Z` = '%f' WHERE `UID` = '%d' AND `CharName` = '%s'", x, y, z, vVars[vehid][vUid], pVars[playerid][pCharName]);
				mysql_query(queryStr);
				
				mainStr[0] = EOS;
				strcat(mainStr, "Pojazd zosta� pomy�lnie zaparkowany w nowym miejscu.\n");
				strcat(mainStr, "Zaleca si� jego respawn, aby zachowa� zmiany.");
				ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_MSGBOX, "Informacja", mainStr, "OK", "");
			}
			return 1;
		} else if(strfind(opt, "z", true) == 0 || strfind(opt, "zamknij", true) != -1) {
			new Float:x, Float:y, Float:z;
			new vehid = actualVehicle[playerid];
			
			if(vehid == INVALID_VEHICLE_ID) {
				return 1;
			}
			
			GetVehiclePos(vVars[vehid][vId], x, y, z);
			
			if(IsPlayerInRangeOfPoint(playerid, 2.0, x, y, z) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
				if(vehicleNonEngine(GetPlayerVehicleID(playerid))) {
					return GameTextForPlayer(playerid, "~g~Pojazdy bez silnika nie~n~maja zamkow.", 5000, 6);
				} else {
					ApplyAnimation(playerid, "INT_HOUSE", "wash_up", 4.1, 0, 1, 1, 1, 1, 1);
				
					if(!vVars[vehid][vLock]) {
						GameTextForPlayer(playerid, "~w~Pojazd ~r~zamkniety", 5000, 6);
						
						vVars[vehid][vLock] = true;
					} else {
						GameTextForPlayer(playerid, "~w~Pojazd ~g~otwarty", 5000, 6);
						
						vVars[vehid][vLock] = false;
					}
				}
			}
			return 1;
		} else if(strfind(opt, "info", true) != -1) {
			new str[64], vehid = actualVehicle[playerid];
			new Float:vHp;
			
			if(vehid == INVALID_VEHICLE_ID) {
				return 1;
			}
			
			GetVehicleHealth(vVars[vehid][vId], vHp);
			
			mainStr[0] = EOS;	
			format(mainStr, sizeof(mainStr), "~p~UID~w~: %d___~p~Owner: ~w~9:%d__(0) ~p~Model~w~: %d~n~~p~SAMP ID~w~: %d___~p~Kolor~w~: %d:%d__~p~HP~w~: %0.1f",
			vVars[vehid][vUid], vVars[vehid][vOUid], vVars[vehid][vModelId], vVars[vehid][vId], vVars[vehid][vColor1], vVars[vehid][vColor2], vHp);
			TextDrawSetString(vehicleStats[playerid][0], mainStr);
			
			format(str, sizeof(str), "~b~Przebieg~w~: %0.1fkm ~b~Paliwo~w~: %0.1f", vVars[vehid][vMileage], vVars[vehid][vFuel]);
			TextDrawSetString(vehicleStats[playerid][1], str);
			
			for(new i = 0; i < 2; i++) {
				TextDrawShowForPlayer(playerid, vehicleStats[playerid][i]);
			}
			
			SetTimerEx("hideVehicleStats", 15000, false, "i", playerid);
			return 1;
		} else if(strfind(opt, "namierz", true) != -1) {
			new Float:x, Float:y, Float:z;
			new vehid = actualVehicle[playerid];
		
			if(vehid == INVALID_VEHICLE_ID) {
				return 1;
			}
		
			GetVehiclePos(vVars[vehid][vId], x, y, z);
			
			if(vehCP[vehid] == -1 && vehMapIcon[vehid] == -1) {
				DestroyDynamicMapIcon(vehMapIcon[vehid]);
				DestroyDynamicCP(vehCP[vehid]);
				
				vehCP[vehid] = CreateDynamicCP(x, y, z, 2.0, 0, 0, -1, 100, -1, 0);
				vehMapIcon[vehid] = CreateDynamicMapIcon(x, y, z, 55, 0, 0, -1, -1, 4000, MAPICON_GLOBAL, -1, 0);
			}
			
			GameTextForPlayer(playerid, "~y~Pojazd zostal pomyslnie namierzony.", 5000, 3);
			return 1;
		} else if(strfind(opt, "reset", true) != -1) {
			new vehid = actualVehicle[playerid];
			
			if(vehid == INVALID_VEHICLE_ID) {
				return 1;
			}
			
			DestroyDynamicMapIcon(vehMapIcon[vehid]);
			DestroyDynamicCP(vehCP[vehid]);
			
			vehCP[vehid] = -1;
			vehMapIcon[vehid] = -1;
			return 1;
		} else if(strfind(opt, "opis", true) != -1) {
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				new vehStr[64];
				new vehid = actualVehicle[playerid];
				
				if(sscanf(params, "s[32]s[64]", opt, vehStr)) {
					return SendClientMessage(playerid, COLOR_GRAY, "Tip: /v opis [Tresc]");
				}
				
				format(vVars[vehid][vDescInfo], 64, vehStr);
				UpdateDynamic3DTextLabelText(vVars[vehid][vDesc], COLOR_PURPLE, vVars[vehid][vDescInfo]);
				
				SendClientMessage(playerid, COLOR_GRAY, "Opis pojazdu ustawiony (aby go usun��, wpisz /opis usun):");
				SendClientMessage(playerid, COLOR_PURPLE, vVars[vehid][vDescInfo]);
			}
			return 1;
		} else {
			return SendClientMessage(playerid, COLOR_GRAY, "Tip: /v [zaparkuj/z(amknij)/info/namierz/reset]");
		}
	}
	return 1;
}

CMD:g(playerid, params[]) {
	if(pVars[playerid][pFraction] < 1) {
		return 1;
	}
	
	if(!showFracsInfo[playerid]) {
		new tmpFracId = checkFractionSrvIdForPlayer(playerid);
		new tmp[32];
		
		format(tmp, sizeof(tmp), "~b~1  ~w~%s (%d)", fVars[tmpFracId][fName], fVars[tmpFracId][fUid]);
		TextDrawSetString(fractionsInfo[playerid][1], tmp);
		
		if(isPlayerDuty[playerid] && pVars[playerid][pDuty]) {
			format(tmp, sizeof(tmp), "~w~%dm duty", pVars[playerid][pDuty]);
			TextDrawSetString(fractionsInfo[playerid][2], tmp);
		}
		
		for(new i = 0; i < 15; i++) {
			TextDrawShowForPlayer(playerid, fractionsInfo[playerid][i]);
		}
		
		SelectTextDraw(playerid, 0xFF000044);
		
		showFracsInfo[playerid] = true;
	} else {
		for(new i = 0; i < 15; i++) {
			TextDrawHideForPlayer(playerid, fractionsInfo[playerid][i]);
		}
		
		CancelSelectTextDraw(playerid);
		
		showFracsInfo[playerid] = false;		
	}
	return 1;
}

CMD:zamknij(playerid, params[]) {
	mainStr[0] = EOS;
	
	format(mainStr, sizeof(mainStr), "* %s zamyka drzwi na klucz.", pVars[playerid][pCharName]);
	sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	
	format(mainStr, sizeof(mainStr), "* %s otwiera drzwi kluczem.", pVars[playerid][pCharName]);
	sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	return 1;
}

CMD:przeszukaj(playerid, params[]) {
	new pId, i;
	new str[256];
	new tmpIVars[MAX_ITEMS][2];
	
	if(sscanf(params, "i", pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /przeszukaj [ID Gracza]");
	}
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `UID`, `Name` FROM `Items` WHERE `OUID` = '%d' ORDER BY `Name` ASC", pVars[pId][pUid]);
	mysql_query(queryStr);
	mysql_store_result();
	
	while(mysql_fetch_row(queryStr, "|")) {
		sscanf(queryStr, "p<|>is[32]", tmpIVars[i][0], tmpIVars[i][1]);
		format(str, sizeof(str), "%s\n{FFFFFF}%d\t0x\t%s", str, tmpIVars[i][0], tmpIVars[i][1]);
		
		i++;
	}
	
	mysql_free_result();
	ShowPlayerDialog(playerid, DIALOG_DEFAULT, DIALOG_STYLE_LIST, "Przedmioty", str, "OK", "Zamknij");
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~n~~n~~n~~n~~n~~n~~n~~y~Gotowka ~h~~y~%s~r~: ~w~$%d", pVars[pId][pCharName], pVars[pId][pMoney]);
	GameTextForPlayer(playerid, mainStr, 10000, 3);
	
	format(mainStr, sizeof(mainStr), "* %s przeszuka� %s.", pVars[playerid][pCharName], pVars[pId][pCharName]);
	sendDistanceMessage(playerid, 30.0, mainStr, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	return 1;
}

CMD:report(playerid, params[]) {
	new str[256], reason[128], pId;
	
	if(usedCmdReport[playerid]) {
		SendClientMessage(playerid, COLOR_WHITE, "Mo�esz wysy�a� tylko jeden raport na minut�. Spokojnie, albo kto� przygl�da si� ju� sytuacji,");
		SendClientMessage(playerid, COLOR_WHITE, "albo tak czy inaczej wszyscy s� zaj�ci innym raportem i powielanie Twojego nic nie zmieni.");
		
		SetTimerEx("refreshCmds", 60000, false, "ii", playerid, 1);
		return 1;
	}
	
	if(sscanf(params, "is[128]", pId, reason)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /report [ID Gracza] [Tre��]");
	}
	
	usedCmdReport[playerid] = true;
	
	format(str, sizeof(str), "{FF0000}Wys�ano: [ID %d]%s: %d %s. (%s)", playerid, pVars[playerid][pCharName], pId, reason, pVars[pId][pCharName]);
	SendClientMessage(playerid, COLOR_WHITE, str);
	
	SendClientMessage(playerid, COLOR_WHITE, "{A52A2A}Pami�taj prosz�, �e /raport s�u�y do raportowania bi꿹cych sytuacji z gry.");
	SendClientMessage(playerid, COLOR_WHITE, "{A52A2A}Nie ma tu systemu kolejkowania pr�b i prawie na pewno zostan� one pomini�te.");
	SendClientMessage(playerid, COLOR_WHITE, "{A52A2A}Je�eli masz jaki� problem lub pro�b�, napisz temat w odpowiednim dziale naszego forum.");
	SendClientMessage(playerid, COLOR_WHITE, "{A52A2A}Prosimy NIE powtarza� raport�w. Nie zwi�ksza to widoczno�ci, a IRYTUJE administracj�.");
	
	SendClientMessage(pId, COLOR_WHITE, "{A52A2A}Hej! W�a�nie wys�ano na Ciebie raport. Ca�kiem mo�liwe, �e zrobi�e�(a�) co�, co");
	SendClientMessage(pId, COLOR_WHITE, "{A52A2A}uprzykrzy�o gr� innej osobie. Ka�dy pope�nia b��dy, ale pami�taj, �e w tej grze chodzi");
	SendClientMessage(pId, COLOR_WHITE, "{A52A2A}o czerpanie przyjemno�ci z interakcji z innymi graczami. Zastan�w si�, kt�ra z twoich");
	SendClientMessage(pId, COLOR_WHITE, "{A52A2A}czynno�ci ma�o odzwierciedla prawdziwe �ycie lub odstaje od gry reszty os�b.");
	SendClientMessage(pId, COLOR_WHITE, "{A52A2A}Czy na pewno masz na uwadze r�wnie� innych graczy i ich rozgrywk�?");
	SendClientMessage(pId, COLOR_WHITE, "{A52A2A}Spokojnie, zawsze weryfikujemy raporty.");
	return 1;
}

CMD:raport(playerid, params[]) {
	return pc_cmd_report(playerid, params);
}

CMD:pasy(playerid, params[]) {
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER) {
		new vehid = actualVehicle[playerid];
		
		if(vVars[vehid][vModelId] == 509) {
			return GameTextForPlayer(playerid, "~y~Ten pojazd nie ma pasow.", 5000, 3);
		}
		
		if(!hasBelts[playerid]) {
			GameTextForPlayer(playerid, "~w~Pasy ~g~zapiete", 5000, 6);
		
			hasBelts[playerid] = true;
		} else {
			GameTextForPlayer(playerid, "~w~Pasy ~r~odpiete", 5000, 6);
		
			hasBelts[playerid] = false;
		}
	}
	return 1;
}

CMD:pokoj(playerid, params[]) {
	if(insidedHotel[playerid]) {
		return GameTextForPlayer(playerid, "~g~Znajdujesz sie juz w hotelu.", 5000, 3);
	}
	
	new tmpDoorId = pVars[playerid][pDoors];
	
	if(dVars[tmpDoorId][dType] == D_HOTEL && pVars[playerid][pVw] != 0 && pVars[playerid][pInt] != 0) {
		if(!pVars[playerid][pHotel]) {
			mainStr[0] = EOS;
			
			strcat(mainStr, "Je�eli wynajmiesz tu pok�j, raz na 24h, z Twojego\nkonta b�dzie");
			strcat(mainStr, "pobierana op�ata $10.\n\nPrzez pierwsze 10 godzin gry hotele s� darmowe.");
			ShowPlayerDialog(playerid, DIALOG_SHOW_HOTEL_OPTS, DIALOG_STYLE_MSGBOX, "Zameldowanie w hotelu", mainStr, "Wynajmij", "Anuluj");
		} else {
			SetPlayerInterior(playerid, 1);
			SetPlayerPos(playerid, 2216.12, -1076.30, 1050.48);
			SetPlayerVirtualWorld(playerid, random(1000));

			insidedHotel[playerid] = true;			
		}
	}
	return 1;
}

CMD:tankuj(playerid, params[]) {
	searchGasPumps(playerid);
	return 1;
}

CMD:bus(playerid, params[]) {
	searchPlayerBusStop(playerid);
	return 1;
}

CMD:bankomat(playerid) {
	return 1;
}

CMD:wyrzuc(playerid, params[]) {
	new pId;
	
	if(sscanf(params, "i", pId)) {
		return SendClientMessage(playerid, COLOR_GRAY, "Tip: /wyrzuc [ID gracza]");
	}
	
	RemovePlayerFromVehicle(pId);
	
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "~h~~g~%s wyrzuca cie z~n~~y~pojazdu.", pVars[playerid][pCharName]);
	GameTextForPlayer(pId, mainStr, 5000, 3);
	return 1;
}

CMD:dajprawojazdy(playerid, params[]) {
	new playerToGive; // Id gracza, ktory ma dostac prawo jazdy
	new fracId = checkFractionSrvIdForPlayer(playerid);
	new str[2];
	
	mainStr[0] = EOS;
	
	if(strfind(fVars[fracId][fName], "Urzad Miasta Los Santos", false) != -1) {
		if(isPlayerDuty[playerid]) {
			if(sscanf(params, "s[2]i", str, playerToGive)) {
				return SendClientMessage(playerid, COLOR_WHITE, "U�ycie komendy /dajprawojazdy [A|B|C] [Id gracza].");
			}
			
			if(!IsPlayerConnected(playerToGive)) {
				return GameTextForPlayer(playerid, "~r~Nie ma takiego gracza.", 3000, 3);
			}
			
			if(strfind(str, "A", true) != -1) {
				format(mainStr, sizeof(mainStr), "[Frakcja]: Dales prawo jazdy A %s.", pVars[playerToGive][pCharName]);
			//	pVars[playerToGive][pDriverLicenseA] = 1;
				
				SendClientMessage(playerid, COLOR_WHITE, mainStr);
				format(mainStr, sizeof(mainStr), "[Urzad]: Otrzymales prawo jazdy A.");
				SendClientMessage(playerToGive, COLOR_WHITE, mainStr);
			} else if(strfind(str, "B", true) != -1) {
				format(mainStr, sizeof(mainStr), "[Frakcja]: Dales prawo jazdy B %s.", pVars[playerToGive][pCharName]);
				//Narazie pDriverLicense, pozniej bedzie pDriverLicenseB
				pVars[playerToGive][pDriverLicense] = 1;
				
				SendClientMessage(playerid, COLOR_WHITE, mainStr);
				format(mainStr, sizeof(mainStr), "[Urzad]: Otrzymales prawo jazdy B.");
				SendClientMessage(playerToGive, COLOR_WHITE, mainStr);
			} else if(strfind(str, "C", true) != -1) {
				format(mainStr, sizeof(mainStr), "[Frakcja]: Dales prawo jazdy C %s.", pVars[playerToGive][pCharName]);
			//	pVars[playerToGive][pDriverLicenseC] = 1;
				
				SendClientMessage(playerid, COLOR_WHITE, mainStr);
				format(mainStr, sizeof(mainStr), "[Urzad]: Otrzymales prawo jazdy C.");
				SendClientMessage(playerToGive, COLOR_WHITE, mainStr);
			}
		}
	}
	return 1;
}

CMD:duty(playerid) {
	new fracId = checkFractionSrvIdForPlayer(playerid);
	
	mainStr[0] = EOS;
	
	if(pVars[playerid][pFraction] != 0) {
		if(isPlayerDuty[playerid]) {
			format(mainStr, sizeof(mainStr), "~w~Schodzisz ze sluzby~n~%s", fVars[fracId][fName]);
			GameTextForPlayer(playerid, mainStr, 5000, 3);
			
			pVars[playerid][pDuty] = 0;
			isPlayerDuty[playerid] = false;
		} else {
			format(mainStr, sizeof(mainStr), "~w~Wchodzisz na sluzbe~n~%s", fVars[fracId][fName]);
			GameTextForPlayer(playerid, mainStr, 5000, 3);
			
			isPlayerDuty[playerid] = true;
		}
	}
	return 1;
}

/*CMD:zaprosdofrakcji(playerid, params[]) {
	new playerToGive, fractionId;
	
	mainStr[0] = EOS;
	
	if(sscanf(params, "i", playerToGive)) {
		
	} else {
		fractionId = pVars[playerid][pFraction];
		
		format(mainStr, sizeof(mainStr), "Otrzymano zaproszenie do frakcji %s.", fVars[fractionId][fName]);
		ShowPlayerDialog(playerToGive, DIALOG_SHOW_FRACTION_INVITE, DIALOG_STYLE_MSGBOX, "Zaproszenie do frakcji", mainStr, "Ok", "Anuluj");
	}
	return 1;
}

CMD:telefon(playerid, params[]) {
	return 1;
}*/

CMD:naprawsilnik(playerid, params[]) {
	if(casualJob[playerid] == PART_TIME_JOB_MECHANIC) {
		new toPlayerId, Float: x, Float: y, Float: z;
		
		if(sscanf(params, "i", toPlayerId)) {
			return SendClientMessage(playerid, COLOR_WHITE, "Uzycie komendy /Naprawsilnik [Id gracza].");
		}
		
		new vehid = actualVehicle[toPlayerId];
		
		SendClientMessage(playerid, COLOR_WHITE, "[Mechanik]: Gracz.");
		GetPlayerPos(playerid, x, y, z);
		
		mainStr[0] = EOS;
		format(mainStr, sizeof(mainStr), "actualVehicle[%d] = %d", toPlayerId, actualVehicle[toPlayerId]);
		SendClientMessage(playerid, COLOR_WHITE, mainStr);
		
		if(IsPlayerInRangeOfPoint(playerid, 5.0, x, y, z)) {
			if(IsPlayerInAnyVehicle(toPlayerId)) {
				vVars[vehid][vEngineHp] = 320.0;
				
				SetVehicleHealth(vVars[actualVehicle[toPlayerId]][vId], vVars[vehid][vEngineHp]);
			} else {
				SendClientMessage(playerid, COLOR_WHITE, "[Mechanik]: Gracz musi znajdowac sie w pojezdzie.");
			}
		} else {
			SendClientMessage(playerid, COLOR_WHITE, "[Mechanik]: Jestes za daleko od gracza.");
		}
	} else {
		return 0;
	}
	return 1;
}

CMD:naprawkaroserie(playerid, params[]) {
	if(casualJob[playerid] == PART_TIME_JOB_MECHANIC) {
		new toPlayerId, Float: x, Float: y, Float: z;
		
		if(sscanf(params, "i", toPlayerId)) {
			return SendClientMessage(playerid, COLOR_WHITE, "Uzycie komendy /Naprawkaroserie [Id gracza].");
		}
		
		new vehid = actualVehicle[toPlayerId];
		
		SendClientMessage(playerid, COLOR_WHITE, "[Mechanik]: Gracz.");
		GetPlayerPos(playerid, x, y, z);
		
		if(IsPlayerInRangeOfPoint(playerid, 5.0, x, y, z)) {
			if(IsPlayerInAnyVehicle(toPlayerId)) {
				RepairVehicle(vVars[actualVehicle[toPlayerId]][vId]);
				SetVehicleHealth(vVars[actualVehicle[toPlayerId]][vId], vVars[vehid][vEngineHp]);
			} else {
				SendClientMessage(playerid, COLOR_WHITE, "[Mechanik]: Gracz musi znajdowac sie w pojezdzie.");
			}
		} else {
			SendClientMessage(playerid, COLOR_WHITE, "[Mechanik]: Jestes za daleko od gracza.");
		}
	} else {
		return 0;
	}
	return 1;
}

CMD:frakcja(playerid) { // panel frakcji 
	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "Zarz�dzanie rangami\nZarz�dzanie pojazdami");
	ShowPlayerDialog(playerid, DIALOG_SHOW_FRACTION_PANEL, DIALOG_STYLE_LIST, "Panel Frakcji", mainStr, "Wybierz", "Anuluj");
	return 1;
}

CMD:cennik(playerid, params[]) {
	if(casualJob[playerid] == PART_TIME_JOB_MECHANIC) {
		new toPlayerId;
		
		mainStr[0] = EOS;
		if(sscanf(params, "i", toPlayerId)) {
			return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[CMD]{FFFFFF}: U�ycie komendy /cennik [Id gracza].");
		}
		
		if(IsPlayerInAnyVehicle(toPlayerId)) {
			new priceForVehHp, priceForVehVisual; // priceForVehVisualHp
			
			priceForVehHp = getPriceForRepairVehicle(vVars[actualVehicle[toPlayerId]][vId]);
			format(mainStr, sizeof(mainStr), "Naprawa silnika\t$%i\nNaprawa karoserii\t$0\nZmiana koloru", priceForVehHp);
			
			priceForVehHp = getPriceForRepairVehicle(vVars[actualVehicle[toPlayerId]][vId]);
			priceForVehVisual = getPriceForRepairVehicleVisual(vVars[actualVehicle[toPlayerId]][vId]);
			format(mainStr, sizeof(mainStr), "Naprawa silnika \t$%i\nNaprawa karoserii\t$%i\nZmiana koloru", priceForVehHp, priceForVehVisual);
			ShowPlayerDialog(toPlayerId, DIALOG_SHOW_PRICE_LIST_MECHANIC, DIALOG_STYLE_LIST, "Cennik", mainStr, "Wybierz", "Anuluj");
		} else {
			return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[CMD]{FFFFFF}: Gracz musi byc w poje�dzie.");
		}
	} else {
		return 0;
	}
	return 1;
}

CMD:wybierzzlecenie(playerid) {
	new vehicleid;
	
	if(casualJob[playerid] == PART_TIME_JOB_DELIVERY) {
		if(IsPlayerInAnyVehicle(playerid)) {
			vehicleid = GetPlayerVehicleID(playerid);
			
			if(isCar(vehicleid)) {
				//ShowPlayerDialog(playerid);
			} else {
				return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[Praca]{FFFFFF}: Musisz byc w odpowiednim poje�dzie.");
			}
		}
	}
	
	if(casualJob[playerid] == PART_TIME_JOB_TRUCK) {
		if(IsPlayerInAnyVehicle(playerid)) {
			vehicleid = GetPlayerVehicleID(playerid);
			
			if(isTruck(vehicleid)) {
				//ShowPlayerDialog(playerid);
			} else {
				return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[Praca]{FFFFFF}: Musisz byc w odpowiednim poje�dzie.");
			}
		}
	}
	return 1;
}

#endif 