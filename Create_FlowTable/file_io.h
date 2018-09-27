int		build_flow_table(struct flow_struct *, double *, double *, int *, int *, int *, double *,
	     int, int, int, int, double);
void	header_help(int *maxr, int *maxc, char* fndem);
int		find_stream(struct flow_struct *, int, int *);
void	find_max_flna(struct flow_struct *flow_table, int curr, int *str_inx);
int		find_patch(int, struct flow_struct *, int);
int		check_neighbours(int er, int ec, int *patch, double *dem, int *stream,
struct  flow_struct *flow_entry, int num_adj, int maxr, int maxc, int sc_flag, double cell);
void	input_prompt(int *maxr, int *maxc, char *filename, char *fndem, char *fnslope,
					char *fnpatch, char *fnstream, char *fnroads, char *fntable, int arc_flag);

void	add_roads(struct flow_struct *, int, double);
void 	route_roads_to_patches(struct flow_struct *, int,double, int);
void	compute_gamma(struct flow_struct *, int, double, int);
void	compute_upslope_area(struct flow_struct *, int, int, double);
void	compute_dist_from_road(struct flow_struct *, int, std::ofstream &, double);
void	compute_drainage_density(struct flow_struct *, int, double);
void	remove_pits(struct flow_struct *, int, int, double, std::ofstream &);

void	input_ascii_int(int *, char *, int, int, int);
void	input_ascii_double(double *, char *, int, int, int);
void	input_ascii_sint(long int *, char *, int, int, int);
void	print_flow_table(int, struct flow_struct *, int, double, char *, double);
void	print_drain_stats(int, struct flow_struct *);
void	adjust_pit(struct flow_struct *, int, int, double, double);
