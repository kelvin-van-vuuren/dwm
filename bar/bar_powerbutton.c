int
width_powerbutton(Bar *bar, BarWidthArg *a)
{
	return TEXTW(powerbutton);
}

int
draw_powerbutton(Bar *bar, BarDrawArg *a)
{
	Monitor *m = bar->mon;

	return drw_text(drw, a->x, 0, a->w, bh, lrpad / 2, powerbutton, 0);
}

int
click_powerbutton(Bar *bar, Arg *arg, BarClickArg *a)
{
	return ClkPowerButton;
}
