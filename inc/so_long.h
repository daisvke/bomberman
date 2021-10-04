/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:19:35 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/04 04:38:11 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include <mlx.h>
# include <X11/X.h>

# include "so_long_macros.h"
# include "so_long_structs.h"
# include "get_next_line.h"

/*
** put_to_terminal
*/
void	sl_put_colored_str_to_terminal(char *str, char *color);
void	sl_put_steps_on_terminal(t_env *env);
void	sl_put_str_to_terminal(char *str);
void	sl_put_nbr_to_terminal(int nbr);

/*
** system calls
*/
void	ft_close(t_env *env, int fd);
void	*ft_free(void *ptr);
void	*ft_malloc(t_env *env, size_t num, size_t size);
int		ft_open(t_env *env, char *filename);

/*
** utils
*/
t_coord	sl_assign_pos(int x, int y);
char	*ft_itoa(t_env *env, int n);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(char *str);

/*
** init
*/
void	sl_check_errors_1(t_env *env);
void	sl_init_all(t_env *env, char *argv[]);
void	sl_init_array(int *array, size_t size);
t_count	sl_init_counter(void);
void	sl_init_buffers(t_env *env);
void	sl_init_errors(t_env *env);
void	sl_init_mlx(t_env *env, int width, int height);
void	sl_init_set_bomb(t_items *bomb, bool draw, t_coord pos, int size);
void	sl_init_sprite(t_sprite *sprite, int x, int y, int speed);

/*
** load textures
*/
void	sl_load_all_textures(t_env *env);
void	sl_load_ennemies(t_env *env);
void	sl_load_ennemies_horizontal(t_env *env);
void	sl_load_ennemies_vertical(t_env *env);
void	sl_load_exit(t_env *env);
void	sl_load_texture(t_env *env, t_img *img, char *path_to_file);
void	sl_load_white_bomber(t_env *env);

void	sl_handle_keypress_bb(int keycode, t_env *env);
/*
** keypress
*/
int		sl_handle_keypress(int keycode, t_env *env);
int		sl_handle_keyrelease(int keycode, t_env *env);

/*
** parsing
*/
void	sl_assign_collectible_type_randomly(\
	t_env *env, t_coord pos, int *count);
t_info	sl_assign_info(char code, int i, int err);
void	sl_check_counter(t_env *env, t_count counter);
void	sl_check_errors_2(t_env *env, int res);
void	sl_parse_map(t_env *data, char *filename);
void	sl_populate_map_with_textures(\
	t_env *env, char char_to_check, t_coord pos, t_count *counter);

/*
** put to window
*/
void	sl_put_collectible_count_to_window(t_env *env);
void	sl_put_message_at_start(t_env *env);
void	sl_put_move_count_to_window(t_env *env);
void	sl_put_centered_message_to_window(t_env *env, char *message);
void	sl_put_counts_to_window(t_env *env);
void	sl_put_stage_name(t_env *env);

/*
** render
*/
void	sl_draw_collectibles(t_env *env);
void	sl_draw_collectibles_by_category(\
	t_env *env, t_items *items, t_img *img, int max);
int		sl_get_color_from_img(t_img *img, int x, int y);
void	sl_img_pixel_put(t_img *img, t_coord pos, int color, bool mask);
void	sl_put_buffer_bkgd_to_img(t_env *env);
int		sl_render(t_env *data);
void	sl_render_background(t_env *data);
void	sl_render_bloc_with_xpm(\
	t_img *img, t_img *xpm_img, t_coord pos, bool mask);
void	sl_render_bombs(t_env *env);
void	sl_render_buffer_bloc_with_xpm(\
	int **buffer, t_img *xpm_img, t_coord pos);
void	sl_render_buffer_green_tile(t_env *env, t_coord pos);
int		sl_render_buffer_with_colored_bloc(\
	int **buffer, int color, t_coord pos);
int		sl_render_colored_bloc(t_img *img, int color, t_coord pos);
void	sl_read_direction_and_animate_sprite(\
	t_env *env, t_sprite_info *info, t_img_patterns *img);
void	sl_render_ennemies(t_env *env);
void	sl_render_green_tile_by_direction(\
	t_env *env, int curr_dir, t_coord pos);
void	sl_render_p1(t_env *env);
void	sl_replace_with_green_tile(t_env *env, t_coord pos);

/*
** texture interactions
*/
void	sl_find_and_turn_off_item(t_items *items, int max, int x, int y);
void	sl_handle_textures_while_moving(\
	t_env *env, int apply_to, t_coord delta);

/*
** animate sprites
*/
void	sl_animate_sprite(\
	t_env *env, t_sprite_info *info, t_states *img, t_coord coord);
int		sl_is_collectible(char elem_to_check);
void	sl_put_back_exit_on_map(t_env *env);

/*
** ennemy
*/
void	sl_assign_ennemy_curr_dir(t_sprite *sprite, int i);
void	sl_determine_ennemy_direction(t_env *env, t_sprite *sprite);
void	sl_get_max_len(t_sprite *sprite, int len_array[]);
int		sl_keep_direction_if_no_wall(\
	char **map, t_coord bomb, int curr_dir, t_coord pos);
void	sl_read_and_animate_ennemies(t_env *env);

/*
** update position
*/
void	sl_update_player_pos_on_map(\
	t_env *env, t_sprite_info *info, int x, int y);
void	sl_update_sub_pos(t_sprite *sprite, t_img *img, t_coord delta);
void	sl_update_sub_pos_state_0(t_sprite *sprite, t_states *img, t_coord pos);
void	sl_update_sub_pos_state_1(t_sprite *sprite, t_states *img, t_coord pos);
void	sl_update_sub_pos_state_2(\
	t_env *env, t_sprite_info *info, t_states *img, t_coord coord);

/*
** bomb
*/
void	sl_check_each_element(t_env *env, char **map, int x, int y);
void	sl_check_what_is_affected_by_the_explosion(\
	t_env *env, t_items *bomb, t_coord pos);
void	sl_clear_segments_of_exploding_bomb(\
	t_env *env, t_items *bomb, t_coord pos);
void	sl_draw_segments_of_exploding_bomb(\
	t_env *env, t_items *bomb, t_coord pos);
void	sl_set_bomb(t_env *env, t_items *bomb);

/*
** death
*/
void	sl_kill_ennemy(t_env *env, t_sprite *ennemy);
void	sl_kill_p1(t_env *env);

/*
** errors
*/
char	*sl_get_err_message_from_err_code(int err_code);
void	sl_print_err_message(int err_code);

/*
** free
*/
void	sl_free_buffer(int *buffer[], int height);
void	sl_free_map(t_env *env, char *map[]);
void	sl_free_map_when_not_complete(char *map[], int height);

/*
** exit game
*/
int		sl_exit_game(t_env *env);
void	sl_exit_when_game_clear(t_env *env);
void	sl_exit_when_game_over(t_env *env);
void	sl_put_err_code_and_exit_game(t_env *env, int err_code);
void	sl_put_err_code_and_exit_if_map_is_incomplete(t_env *env, int i);

#endif
