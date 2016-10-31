set table "Akishin.pgf-plot.table"; set format "%.5f"
set samples 100; set parametric; plot [t=-4.:4.] t*(t-1.5)*(t+1.5),t
