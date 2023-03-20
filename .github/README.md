<div align="center">
    <img src="https://user-images.githubusercontent.com/54939625/226377372-38b186c0-2999-4dc1-ad8c-546bfc27ed7e.svg" alt="dwm logo">
</div>
<div align="center">
Custom build of <a href="https://dwm.suckless.org">dwm</a>, a dynamic <a href="https://en.wikipedia.org/wiki/Window_manager">window manager</a> for <a href="https://www.x.org/wiki/">X</a>.
</div>
<p></p>
<div align="center">
    	<a href="https://github.com/kelvin-van-vuuren/dwm#about">About</a>
  <span> • </span>
       	<a href="https://github.com/kelvin-van-vuuren/dwm#features">Features</a>
  <span> • </span>
       	<a href="https://github.com/kelvin-van-vuuren/dwm#screenshots">Screenshots</a>
  <span> • </span>
	<a href="https://github.com/kelvin-van-vuuren/dwm#Install">Install</a>
  <span> • </span>
	<a href="https://github.com/kelvin-van-vuuren/dwm#Keybindings">Keybindings</a>
  <p></p>
</div>

![screenshot](https://user-images.githubusercontent.com/54939625/226385460-b71b6e8c-f985-4ca8-9766-6db516307589.jpg)

### About
<a href="https://dwm.suckless.org">dwm</a> is an extremely fast, small, and dynamic <a href="https://en.wikipedia.org/wiki/Window_manager">window manager</a> for <a href="https://www.x.org/wiki/">X</a> written by <a href="https://suckless.org">suckless</a>. The base distribution of this software adheres to the <a href="https://suckless.org/philosophy">suckless philosophy</a> and as a result comes with a very minimal set of features. This fork extends the functionality and appearance of the program through the use of <a href="https://dwm.suckless.org/patches">patches</a> and <a href="https://github.com/kelvin-van-vuuren/dwm/commits/main">other changes to the codebase</a>.

### Features
#### Patches
* [**Restartsig**](https://dwm.suckless.org/patches/restartsig/): restart dwm via ``MOD Shift Control q``.
* [**Restore after restart**](https://dwm.suckless.org/patches/restoreafterrestart/): restore windows to correct tags after restart.
* [**Xresources**](https://dwm.suckless.org/patches/xresources/):  handle settings from <a href="https://en.wikipedia.org/wiki/X_resources">Xresources</a> (see: <a href="https://github.com/kelvin-van-vuuren/dotfiles/blob/main/.config/x11/xresources">example</a>).
* [**Pertag**](https://dwm.suckless.org/patches/pertag/): layout is per tag instead of per screen.
* [**Full gaps**](https://dwm.suckless.org/patches/fullgaps/): control inner / outer gaps between windows via ``MOD [`` / ``MOD ]``.
* [**Terminal name from env var**](https://dwm.suckless.org/patches/environmentvars/): load terminal emulator name from environment variable.
* [**Autostart**](https://dwm.suckless.org/patches/cool_autostart/): auto start list of programs when dwm is run (currently [dwmblocks](https://github.com/kelvin-van-vuuren/dwmblocks-async)).
* [**Cycle layouts**](https://dwm.suckless.org/patches/cyclelayouts/): cycle tag layouts using ``MOD+shift+h/l``.
* [**Move clients**](https://dwm.suckless.org/patches/movestack/): moves clients up/down the current tag's layout's stack using ``MOD+shift+j/k``.
* [**Send window to next/prev mon**](https://dwm.suckless.org/patches/tagothermonitor/): will send selected window to currently selected tag on next / prev monitor using ``MOD+shift+n/p``.
* [**Always center floating windows**](https://dwm.suckless.org/patches/alwayscenter/)
* [**Resize window from any corner**](https://dwm.suckless.org/patches/resizecorners/): previously could only resize a window from the bottom right.
* [**Sticky window**](https://dwm.suckless.org/patches/sticky/): sticky/unsticky a window (display on all tags) with ``MOD+y``
* [**Bottom stack**](https://dwm.suckless.org/patches/bottomstack/): two new layouts with main window appearing taking up horizontal space above stack windows.
#### Bar
The bar has been replaced using the [barmodules](https://github.com/bakkeby/patches/wiki/barmodules) from [bakkeby](https://github.com/bakkeby) which allows the bar to split into separate modules which can then be easily repositioned. Using this patch I have made the following changes:
* [**Status button**](https://github.com/bakkeby/patches/blob/master/dwm/dwm-barmodules-statusbutton-6.3.diff): Status button positioned leftmost on the bar. Icon set to tux (Linux penguin). Clicking on the button will bring up a [dmenu](https://github.com/kelvin-van-vuuren/dmenu) prompt. The highlighting of this button changes when monitor focus changes to indicate currently selected monitor.
* [**Layout menu**](https://dwm.suckless.org/patches/layoutmenu/): layout indicator moved to left of bar after status button. Right click brings up context menu for layout switching.
* **Win title indicator**: Moved to left of bar after layout indicator. Now displays selected window's WM_CLASS attribute instead of WM_NAME with the width of indicator being set to the text length. This gives a cleaner and more concise display of the currently selected window's title.
* [**Win title icons**](https://dwm.suckless.org/patches/winicon/): if available, displays the selected window's icon to left of text in win title indicator (requires imlib2).
* [**Underline highlighted tag**](https://dwm.suckless.org/patches/underlinetags/): tag module centered in the middle of the bar and currently selected tag is underline.
* [**Hide vacant tags**](https://dwm.suckless.org/patches/hide_vacant_tags/): only display tags in tag module which have open windows to save space.
* [**Sticky window indicator**](https://dwm.suckless.org/patches/stickyindicator/): an indicator will display at the top left of the win title module when a window has been stickied. Fills when sticky window is selected.
* [**Power menu**](https://github.com/kelvin-van-vuuren/dwm/commit/bcd29aa019198b28e7f320d88440b02cd68aa154): power menu on the rightmost section of the bar. Clicking opens a power menu in the center of the screen via a [dmenu](https://github.com/kelvin-van-vuuren/dmenu) prompt.
* [**Sys tray**](https://github.com/bakkeby/patches/blob/master/dwm/dwm-barmodules-powerline-6.3.diff): displays clickable icons of open programs which support system tray functionality.
* [**Alpha**](https://dwm.suckless.org/patches/alpha/): change opacity of bar background.

#### Status modules
Status modules are handled using my fork of [dwmblocks-async](https://github.com/kelvin-van-vuuren/dwmblocks-async). The program allows status modules to be updated asynchronously. Modules scripts can be found [here](https://github.com/kelvin-van-vuuren/dwmblocks-async/tree/main/bin). The following patches support status module functionality:
* [**Dwmblocks**](https://github.com/bakkeby/patches/blob/master/dwm/dwm-barmodules-status2d-statuscmd-dwmblocks-extrastatus-6.3.diff): integrates dwmblocks-async into dwm.
* [**Statuscmd**](https://github.com/bakkeby/patches/blob/master/dwm/dwm-barmodules-status2d-statuscmd-dwmblocks-extrastatus-6.3.diff): send signals to dwmblocks when modules on the status bar are clicked. Signals are then handled by dwmblocks and sent to scripts which then provide some functionality.
* [**Status2d**](https://github.com/bakkeby/patches/blob/master/dwm/dwm-barmodules-status2d-statuscmd-dwmblocks-extrastatus-6.3.diff): colours / drawing in status bar.
* [**Extra bar**](https://github.com/bakkeby/patches/blob/master/dwm/dwm-barmodules-status2d-statuscmd-dwmblocks-extrastatus-6.3.diff): Splits status text. This is usually used to have an extra bar at the bottom of screen. However, in conjunction with bar modules patch, it can be used to display two status texts at different locations of single bar. In this case there is one set of status to the right and one to the left.

### Screenshots
![2023-03-20-205726_3840x2160_scrot](https://user-images.githubusercontent.com/54939625/226464441-5c1ba67c-acd8-4f2a-bec3-e4448bac3808.png)
![2023-03-20-191428_3840x2160_scrot](https://user-images.githubusercontent.com/54939625/226443915-e4f99b90-256b-4eb5-9804-e4e16f0c8e02.png)
![screenshot-power-menu](https://user-images.githubusercontent.com/54939625/226444118-853bc5f5-e5d7-498c-96cd-72a315a9c38b.jpg)

### Install
Clone this repo and install with ``rm -rf config.h && sudo make clean install``. Configuration is done via [config.def.h](https://github.com/kelvin-van-vuuren/dwm/blob/main/config.def.h) so any changes will require the program to be recompiled and installed to take effect.
**Note**: this build is intended for use with other software on my system. See my [dotfiles](https://github.com/kelvin-van-vuuren/dotfiles) for my full system config, where [an example of how to run dwm](https://github.com/kelvin-van-vuuren/dotfiles/blob/main/.config/x11/xinitrc) can be found. Also see my builds of related [suckless](https://suckless.org) software:
* [st](https://github.com/kelvin-van-vuuren/st): terminal emulator.
* [dmenu](https://github.com/kelvin-van-vuuren/dmenu): a very useful dynamic menu.
* [slock](https://github.com/kelvin-van-vuuren/slock): screen locker.

My builds of [dmenu](https://github.com/kelvin-van-vuuren/dmenu) and [slock](https://github.com/kelvin-van-vuuren/slock) will be required for some commands that are integrated into this build of dwm to work correctly.

### Tutorial

See the [suckless site](https://dwm.suckless.org/tutorial/) for a brief explanation on how to use the program.

### Keybindings
These are set in [config.def.h](https://github.com/kelvin-van-vuuren/dwm/blob/main/config.def.h#L153). The ``MOD`` key is set to Mod3, which I have [caps lock remapped](https://github.com/kelvin-van-vuuren/dotfiles/blob/main/.local/bin/keyboardsetup) to on my system.
<div align="center">
<table>
<colgroup>
<col style="text-align:center;"/>
<col style="text-align:left;"/>
</colgroup>

<thead>
<tr>
	<th style="text-align:center;">Keys</th>
	<th style="text-align:left;">Function</th>
</tr>
</thead>

<tbody>
<tr>
	<td style="text-align:center;">MOD p</td>
	<td style="text-align:left;">Launch dmenu</td>
</tr>
<tr>
	<td style="text-align:center;">MOD Enter</td>
	<td style="text-align:left;">Launch terminal</td>
</tr>
<tr>
	<td style="text-align:center;">MOD Shift Enter</td>
	<td style="text-align:left;">Launch floating terminal</td>
</tr>
<tr>
	<td style="text-align:center;">MOD =</td>
	<td style="text-align:left;">Brightness up</td>
</tr>
<tr>
	<td style="text-align:center;">MOD -</td>
	<td style="text-align:left;">Brightness down</td>
</tr>
<tr>
	<td style="text-align:center;">MOD '</td>
	<td style="text-align:left;">Lock screen</td>
</tr>
<tr>
	<td style="text-align:center;">MOD Shift '</td>
	<td style="text-align:left;">Launch power menu</td>
</tr>
<tr>
	<td style="text-align:center;">MOD b</td>
	<td style="text-align:left;">Toggle bar</td>
</tr>
<tr>
	<td style="text-align:center;">MOD Shift j</td>
	<td style="text-align:left;">Move window up layout's stack</td>
</tr>
<tr>
	<td style="text-align:center;">MOD Shift k</td>
	<td style="text-align:left;">Move window down layout's stack</td>
</tr>
<tr>
	<td style="text-align:center;">MOD i</td>
	<td style="text-align:left;">Increment number of master windows</td>
</tr>
<tr>
	<td style="text-align:center;">MOD d</td>
	<td style="text-align:left;">Decrement number of master windows</td>
</tr>
<tr>
	<td style="text-align:center;">MOD ,</td>
	<td style="text-align:left;">Decrease master windows screen share</td>
</tr>
<tr>
	<td style="text-align:center;">MOD .</td>
	<td style="text-align:left;">Increase master window's screen share</td>
</tr>
<tr>
	<td style="text-align:center;">MOD j</td>
	<td style="text-align:left;">Select next window in layout's stack</td>
</tr>
<tr>
	<td style="text-align:center;">MOD k</td>
	<td style="text-align:left;">Select previous window in layout's stack</td>
</tr>
<tr>
	<td style="text-align:center;">MOD =</td>
	<td style="text-align:left;">Brightness up</td>
</tr>
<tr>
	<td style="text-align:center;">MOD q</td>
	<td style="text-align:left;">Close selected window</td>
</tr>
<tr>
	<td style="text-align:center;">MOD m</td>
	<td style="text-align:left;">Set layout to monocle</td>
</tr>
<tr>
	<td style="text-align:center;">MOD =</td>
	<td style="text-align:left;">Brightness up</td>
</tr>
<tr>
	<td style="text-align:center;">MOD space</td>
	<td style="text-align:left;">Switch between two most recent layouts</td>
</tr>
<tr>
	<td style="text-align:center;">MOD Shift space</td>
	<td style="text-align:left;">Toggle window floating</td>
</tr>
<tr>
	<td style="text-align:center;">MOD y</td>
	<td style="text-align:left;">Toggle floating window</td>
</tr>
<tr>
	<td style="text-align:center;">MOD y</td>
	<td style="text-align:left;">Toggle floating window</td>
</tr>
<tr>
	<td style="text-align:center;">MOD Shift l</td>
	<td style="text-align:left;">Cycle through layouts</td>
</tr>
<tr>
	<td style="text-align:center;">MOD Shift h</td>
	<td style="text-align:left;">Cycle back through layouts</td>
</tr>
<tr>
	<td style="text-align:center;">MOD y</td>
	<td style="text-align:left;">Toggle floating window</td>
</tr>
<tr>
	<td style="text-align:center;">MOD Shift 0</td>
	<td style="text-align:left;">Show all tags on screen</td>
</tr>
<tr>
	<td style="text-align:center;">MOD y</td>
	<td style="text-align:left;">Toggle floating window</td>
</tr>
<tr>
	<td style="text-align:center;">MOD l</td>
	<td style="text-align:left;">Move focus to next monitor</td>
</tr>
<tr>
	<td style="text-align:center;">MOD h</td>
	<td style="text-align:left;">Move focus to previous monitor</td>
</tr>
<tr>
	<td style="text-align:center;">MOD y</td>
	<td style="text-align:left;">Toggle floating window</td>
</tr>
<tr>
	<td style="text-align:center;">MOD [</td>
	<td style="text-align:left;">Decrease gaps between windows</td>
</tr>
<tr>
	<td style="text-align:center;">MOD ]</td>
	<td style="text-align:left;">Increase gaps between windows</td>
</tr>
<tr>
	<td style="text-align:center;">MOD Shift [</td>
	<td style="text-align:left;">Reset gaps</td>
</tr>
<tr>
	<td style="text-align:center;">MOD Shift ]</td>
	<td style="text-align:left;">Toggle gaps</td>
</tr>
<tr>
	<td style="text-align:center;">MOD Shift n</td>
	<td style="text-align:left;">Send currently selected window to next monitor</td>
</tr>
<tr>
	<td style="text-align:center;">MOD Shift p</td>
	<td style="text-align:left;">Send currently selected window to previous monitor</td>
</tr> 
<tr>
	<td style="text-align:center;">MOD 0-9</td>
	<td style="text-align:left;">Change tag</td>
</tr>
<tr>
	<td style="text-align:center;">MOD Shift 0-9</td>
	<td style="text-align:left;">Send currently selected window to tag</td>
</tr>
<tr>
	<td style="text-align:center;">MOD Shift q</td>
	<td style="text-align:left;">Quit dwm</td>
</tr>
<tr>
	<td style="text-align:center;">MOD Shift Control q</td>
	<td style="text-align:left;">Restart dwm</td>
</tr>
</table>
</div>
