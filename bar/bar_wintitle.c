int
width_wintitle(Bar *bar, BarWidthArg *a)
{
    Monitor *m = bar->mon;
    int w = 0;
 
    if (m->sel) {
	   w = TEXTW(m->sel->name);
	   if (m->sel->icon)
		   w += m->sel->icw + ICONSPACING;
    }

    return w;
}

int
draw_wintitle(Bar *bar, BarDrawArg *a)
{
	int boxs = drw->fonts->h / 9;
	int boxw = drw->fonts->h / 6 + 2;
	int x = a->x, w = a->w;
	Monitor *m = bar->mon;

	if (m->sel) {
        drw_text(drw, x, 0, w, bh, lrpad / 2 + (m->sel->icon ? m->sel->icw + ICONSPACING : 0), m->sel->name, 0);
        if (m->sel->icon) drw_pic(drw, x + lrpad / 2, (bh - m->sel->ich) / 2, m->sel->icw, m->sel->ich, m->sel->icon);
		if (m->sel->isfloating)
			drw_rect(drw, x + boxs, boxs, boxw, boxw, m->sel->isfixed, 0);
        if (m->sel->issticky)
            drw_polygon(drw, x + boxs, m->sel->isfloating ? boxs * 2 + boxw : boxs, stickyiconbb.x, stickyiconbb.y,
                        boxw, boxw * stickyiconbb.y / stickyiconbb.x, stickyicon, LENGTH(stickyicon), Nonconvex,
                        m->sel->tags & m->tagset[m->seltags]);
	} else {
		drw_setscheme(drw, scheme[SchemeNorm]);
		drw_rect(drw, x, 0, w, bh, 1, 1);
	}
	return x + w;
}

int
click_wintitle(Bar *bar, Arg *arg, BarClickArg *a)
{
	return ClkWinTitle;
}
