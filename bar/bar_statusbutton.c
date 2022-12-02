int
width_stbutton(Bar *bar, BarWidthArg *a)
{
	return TEXTW(buttonbar);
}

int
draw_stbutton(Bar *bar, BarDrawArg *a)
{
	Monitor *m = bar->mon;

    if (bar->mon == selmon)
		drw_setscheme(drw, scheme[m == selmon ? SchemeSel : SchemeNorm]);
	return drw_text(drw, a->x, 0, a->w, bh, lrpad / 2, buttonbar, 0);
}

int
click_stbutton(Bar *bar, Arg *arg, BarClickArg *a)
{
	return ClkButton;
}
