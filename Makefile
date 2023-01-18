# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/10 15:53:52 by jjuntune          #+#    #+#              #
#    Updated: 2023/01/18 12:27:06 by jsaarine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = src/
INCLUDE_DIR = src/ include/ build/libsdl2/include/
BUILD_DIR = build/
SCREEN_SHOT_DIR = Images/

libsdl2_makefile = libsdl2/Makefile
libsdl2_lib = $(BUILD_DIR)libsdl2/lib/libSDL2.a
libsdl2_cflags = `$(BUILD_DIR)libsdl2/bin/sdl2-config --cflags`
libsdl2_ldflags = `$(BUILD_DIR)libsdl2/bin/sdl2-config --libs`

FT_LIBRARY = libft/libft.a
YAXML_LIBRARY = YaXML/yaxml.a

SRC_FILES = $(addprefix $(SRC_DIR), main.c \
								input_free.c\
								input_light_and_camera.c\
								input_object.c\
								input_object_utils.c\
								input_object_material.c\
								input_prepare.c\
								input_utils.c\
								initialize.c\
								vector_functions.c\
								vector_functions2.c\
								vector_functions3.c\
								quadratic.c\
								image_render.c\
								edge_detection.c\
								edge_detection_check.c\
								filters.c\
								filter_sepia.c\
								multi_thread_worker.c\
								multi_thread.c\
								key_hooks.c\
								create_screen_shot.c\
								create_screen_shot_name.c\
								perlin_noice.c\
								perlin_noice_maths.c\
								tuple_print.c\
								tuple_new.c\
								tuple_add.c\
								tuple_neg.c\
								tuple_sub.c\
								tuple_mag.c\
								tuple_unit.c\
								tuple_scalar_div.c\
								tuple_scalar_mult.c\
								point_new.c\
								vector_dot.c\
								vector_new.c\
								vector_cross.c\
								vector_reflect.c\
								nearly_equal.c\
								fabs.c\
								int_clamp.c\
								float_clamp.c\
								color.c\
								matrix_equals.c\
								matrix_new.c\
								matrix_multiply.c\
								matrix_row_column_multiply.c\
								matrix_tuple_multiply.c\
								matrix_transpose.c\
								matrix_determinant.c\
								matrix_cofactor.c\
								matrix_minor.c\
								matrix_submatrix.c\
								matrix_print.c\
								matrix_inverse.c\
								matrix_translate.c\
								matrix_scale.c\
								matrix_rotate.c\
								matrix_identity_new.c\
								ray_new.c\
								ray_position.c\
								ray_transform.c\
								sphere.c\
								plane.c\
								cylinder.c\
								cone.c\
								discriminant.c\
								intersection_record.c\
								intersection_new.c\
								intersection_utils.c\
								set_transform.c\
								object_new.c\
								normal_at.c\
								light_new.c\
								material.c\
								lighting.c\
								find_closest_intersection.c\
								img_pixel_put.c\
								scene_new.c\
								scene_intersect.c\
								precompute.c\
								shade_hit.c\
								pattern_at.c\
								pattern_striped.c\
								pattern_grid.c\
								negative_shape.c\
								negative_find_shapes.c\
								camera_coi_transform.c\
								stereoscopy.c\
								motion_new.c\
								motion_move.c\
								motion_set_all.c\
								motion_blur.c\
								is_shadowed.c\
								reflected_color.c\
								color_at.c\
								create_frame.c\
								slice.c\
								parser.c)

OBJCT_FILES = $(subst $(SRC_DIR), $(BUILD_DIR), $(SRC_FILES:.c=.o))

NAME = RT

DEPENDENCY_FILES = $(subst $(SRC_DIR), $(BUILD_DIR), $(SRC_FILES:.c=.dep))
DEPENDENCY_FLAGS = -MT $(@) -MMD -MP -MF $(BUILD_DIR)$(*).dep

LD = gcc
LDFLAGS = $(libsdl2_ldflags) # -flto
CC = gcc
OPTFLAGS = -O3 -flto # PUT BACK IN
CFLAGS = -g -c -Wall -Werror -Wextra  $(addprefix -I, $(INCLUDE_DIR))\
	$(libsdl2_cflags)
#CPPFLAGS = -D_REENTRANT

all: $(NAME)

$(NAME): $(FT_LIBRARY) $(YAXML_LIBRARY) $(SCREEN_SHOT_DIR) $(OBJCT_FILES) | $(BUILD_DIR) 
	$(LD) -g $(OBJCT_FILES) $(LDFLAGS) -o $(NAME) $(FT_LIBRARY) $(YAXML_LIBRARY)

$(OBJCT_FILES): $(libsdl2_lib)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(SCREEN_SHOT_DIR):
	mkdir $(SCREEN_SHOT_DIR)

$(BUILD_DIR)%.o: $(SRC_DIR)%.c
$(BUILD_DIR)%.o: $(SRC_DIR)%.c | $(BUILD_DIR)%.dep
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEPENDENCY_FLAGS) -o $(@) $(<)

$(DEPENDENCY_FILES):

$(libsdl2_makefile):
	if test -d $(BUILD_DIR); then echo exists; else mkdir $(BUILD_DIR); fi
	cd libsdl2 && ./configure --prefix=$(abspath $(BUILD_DIR)libsdl2)\
		--disable-shared --disable-video-wayland
	$(MAKE) --directory=libsdl2

$(libsdl2_lib): $(libsdl2_makefile) | $(BUILD_DIR)
	$(MAKE) --directory=libsdl2 install

$(FT_LIBRARY):
	make -C libft/

$(YAXML_LIBRARY):
	make -C YaXML/ tidy

clean:
	@ rm -f $(OBJCT_FILES)
	make -C libft/ clean
	make -C YaXML/ clean

fclean:
	rm -f RT
	if test -f $(libsdl2_makefile); then $(MAKE) AUTOMAKE=: --directory=libsdl2\
		distclean; fi
	rm -rf $(BUILD_DIR)
	rm -rf $(SCREEN_SHOT_DIR)
	make -C libft/ fclean
	make -C YaXML/ fclean

re: fclean all

.PHONY: all clean fclean re

include $(wildcard $(DEPENDENCY_FILES))
