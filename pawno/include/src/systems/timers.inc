/*
	Project: SAMP-RP
	Author: steeZ (macpilch)
	File: timers.inc
	Date: 29.07.2022
	Modified: 31.07.2022
*/

#if !defined _TIMERS_
#define _TIMERS_

task globalTimer[1000]() {
	foreach(Player, i) {
		if(pVars[i][pHours] > 20) {
			format(mainStr, sizeof(mainStr), "%s (%d)", pVars[i][pCharName], i);
		} else {
			format(mainStr, sizeof(mainStr), "%s (%d, %dh)", pVars[i][pCharName], i, pVars[i][pHours]);
		}
		
		UpdateDynamic3DTextLabelText(pVars[i][p3dInfo], COLOR_WHITE, mainStr);
	
		pVars[i][pSeconds]++;
		
		if(pVars[i][pSeconds] == 60) {
			pVars[i][pMinutes]++;
			pVars[i][pSeconds] = 0;
			
			savePlayerValues(i);
		}
		
		if(pVars[i][pMinutes] == 60) {
			pVars[i][pHours]++;
			pVars[i][pMinutes] = 0;
		}
	}
}

task settingsTimer[30000]() {
	saveServerValues();
}

task townHallBellsTimer[59000]() {
	new hours, minutes, seconds;
	
	gettime(hours, minutes, seconds);
	
	foreach(Player, i) {
		mainStr[0] = EOS;
		
		if(minutes == 0) {
			format(mainStr, sizeof(mainStr), "** Dzwony w ratuszu bij� %d razy. **", hours);
			SendClientMessage(i, COLOR_WHITE, mainStr);
		}
	}
}

Callback:healthDamage(playerid) {
	if(pVars[playerid][pHours] > 20) {
		format(mainStr, sizeof(mainStr), "{FF0000}%s (%d)", pVars[playerid][pCharName], playerid);
	} else {
		format(mainStr, sizeof(mainStr), "{FF0000}%s (%d, %dh)", pVars[playerid][pCharName], playerid, pVars[playerid][pHours]);
	}
	
	UpdateDynamic3DTextLabelText(pVars[playerid][p3dInfo], COLOR_WHITE, mainStr);
	return 1;
}

#endif 