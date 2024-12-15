/* Version: 0.1a (16.12.24) */

/* ### RUSSIAN LANGUAGE INFORMATION
 * Библиотека libEx - набор функций, который может пригодится для использования на совершенно любом SA:MP сервере.
 * Состоит из популярного и частоиспользуемого функционала, который часто используют разработчики.
 * Чаще всего его пишет каждый сам, либо он разбросан единичными функциями по форуму.
 * Мы собираём всё в одном месте - для вашего удобства.
 * Функции библиотеки не будут конфликтовать с вашими - ведь они будут определены только, если такой функции в вашем моде нет.
 * Если конфликт возник - уберите свою функцию, либо определите её до подключения libEx.
 */

/* ### ENGLISH LANGUAGE INFORMATION
 * Info
 */

/* ### Author's and Partner's
 * Author - timmylich. - @timmylich (VK/TG/GitHub/YT), @timmylich_workshop(VK/TG)
 * Partner - Brentwood Project - @brentwood_official (VK/TG/TT). https://bw-p.ru
 * ### Contributor's
 * None
 */

/* ### Path's
 * player - Player's functions.
 */


#if defined _INC_libEx_
    #endinput
#endif
#define _INC_libEx_


/* ### Player Functions:
 *
 * ## HUD:
 * SetScreenFill(playerid, start = 0, main, end = 0)
 */






/* Fill player screen by color / Залить экран игрока цветом
 * color = color in HEX RGBA / Цвет в HEX RGBA
 * start = increase time / Время нарастания
 * main = main time / Основное время
 * end = ending time / Время угасания
 */
stock SetScreenFill(playerid, color, start = 0, main, end = 0)
{
    if(!start)
    {
        SetPVarInt(playerid, !"ScreenColor", color);
        SetPVarInt(playerid, !"ScreenFadeInStep", 0);
        SetPVarInt(playerid, !"ScreenFadeOutStep", (end > 0) ? 255 / (end / 50) : 0);
        SetPVarInt(playerid, !"ScreenAlpha", 255);

        ApplyPlayerScreenColor(playerid, color, 255);

        if(end > 0)
        {
            SetTimerEx(!"ScreenFadeOut", main, false, !"i", playerid);
        }
        return 1;
    }

    SetPVarInt(playerid, !"ScreenColor", color);
    SetPVarInt(playerid, !"ScreenFadeInStep", 255 / (start / 50));
    SetPVarInt(playerid, !"ScreenFadeOutStep", (end > 0) ? 255 / (end / 50) : 0);
    SetPVarInt(playerid, !"ScreenAlpha", 0);

    return SetPVarInt(playerid, !"FadeInTimer", SetTimerEx(!"ScreenFadeIn", 50, true, !"ii", playerid, main));
}
forward ScreenFadeIn(playerid, main);
public ScreenFadeIn(playerid, main)
{
    if(playerid < 0 || playerid >= MAX_PLAYERS) return 0;

    new alpha = GetPVarInt(playerid, !"ScreenAlpha");
    new step = GetPVarInt(playerid, !"ScreenFadeInStep");
    new color = GetPVarInt(playerid, !"ScreenColor");

    alpha += step;
    if(alpha >= 255)
    {
        alpha = 255;
        SetPVarInt(playerid, !"ScreenAlpha", alpha);
        ApplyPlayerScreenColor(playerid, color, alpha);
        KillTimer(GetPVarInt(playerid, !"FadeInTimer"));

        if(GetPVarInt(playerid, !"ScreenFadeOutStep") > 0)
        {
            SetTimerEx(!"ScreenFadeOut", (GetPVarInt(playerid, !"ScreenFadeOutStep") + main), false, !"i", playerid);
        }
        return 1;
    }

    SetPVarInt(playerid, !"ScreenAlpha", alpha);
    return ApplyPlayerScreenColor(playerid,  color, alpha);
}
forward ScreenFadeOut(playerid);
public ScreenFadeOut(playerid)
{
    if(!IsPlayerConnected(playerid)) return 0;

    new alpha = GetPVarInt(playerid, !"ScreenAlpha");
    new step = GetPVarInt(playerid, !"ScreenFadeOutStep");
    new color = GetPVarInt(playerid, !"ScreenColor");

    alpha -= step;
    if (alpha <= 0)
    {
        alpha = 0;
        SetPVarInt(playerid, !"ScreenAlpha", alpha);
        return TextDrawHideForPlayer(playerid, GetPVarInt(playerid, !"ScreenFillTD"));
    }

    SetPVarInt(playerid, !"ScreenAlpha", alpha);
    ApplyPlayerScreenColor(playerid, color, alpha);
    return SetTimerEx(!"ScreenFadeOut", (GetPVarInt(playerid, !"ScreenFadeOutStep")), false, !"i", playerid);
}
stock ApplyPlayerScreenColor(playerid, color, alpha)
{
    new finalColor = (color & 0xFFFFFF00) | (alpha & 0xFF);
    new ScreenFillTD = GetPVarInt(playerid, !"ScreenFillTD");

    TextDrawBackgroundColor(ScreenFillTD, finalColor);
	TextDrawColor(ScreenFillTD, finalColor);
	TextDrawBoxColor(ScreenFillTD, finalColor);
    return TextDrawShowForPlayer(playerid, ScreenFillTD);
}
public OnGameModeInit()
{
    new ScreenFillTD;
    ScreenFillTD = TextDrawCreate(0.0, 0.0, ".");
    SetSVarInt(!"ScreenFillTD", ScreenFillTD);

	TextDrawUseBox(ScreenFillTD, 1);
	TextDrawBoxColor(ScreenFillTD, 0x00000000);
	TextDrawTextSize(ScreenFillTD, 640.000000, 23.000000);
	TextDrawAlignment(ScreenFillTD, 0);
	TextDrawBackgroundColor(ScreenFillTD, 0x00000000);
	TextDrawFont(ScreenFillTD, 3);
	TextDrawLetterSize(ScreenFillTD, 1.000000, 52.200000);
	TextDrawColor(ScreenFillTD, 0x00000000);
	TextDrawSetOutline(ScreenFillTD, 0);
	TextDrawSetProportional(ScreenFillTD, 1);
    TextDrawSetShadow(ScreenFillTD, 0);

    #if defined libEx_OnGameModeInit
        return libEx_OnGameModeInit();
    #else
        return 1;
    #endif
}
#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif

#define OnGameModeInit libEx_OnGameModeInit

#if defined libEx_OnGameModeInit
    forward libEx_OnGameModeInit();
#endif

