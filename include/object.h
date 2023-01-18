/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:56:24 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/18 13:19:08 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "../libft/libft.h"
# include "matrix.h"
# include "tuple.h"
# include "vector.h"
# include "patterns.h"
# include "motion.h"
# include <stdlib.h>

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

enum
{
	SPHERE,
	CYLINDER,
	PLANE,
	CONE,
	SUN,
	POINT,
	SPOT,
};

// For ambient, diffuse, and specular, the typical values are between 0 and 1. 
// For shininess, values between 10 (very large highlight) 
// and 200 (very small highlight) seem to work best, 
// though there is no actual upper bound.

typedef struct s_material
{
	t_color		color;
	double		ambient;
	double		diffuse;
	double		specular;
	double		shininess;
	double		reflective;
	t_pattern	pattern;
	int			normal_disturbance;
}	t_material;

typedef struct s_object
{
	t_point			loc;
	t_point			coi;
	t_vector		up;
	t_vector		rot;
	t_tuple			scale;
	double			size;
	double			brightness;
	int				type;
	int				negative;
	size_t			id;
	t_matrix		transform;
	t_matrix		inverse_transform;
	t_tuple			color;
	t_material		material;
	t_motion_blur	motion;
}					t_object;

typedef struct s_abc
{
	double			a;
	double			b;
	double			c;
}					t_abc;

typedef struct s_abcd
{
	double			a;
	double			b;
	double			c;
	double			d;
}					t_abcd;

typedef struct s_intersections
{
	t_vec			vec;
}					t_intersections;

typedef struct s_hit_record
{
	t_point			hit_loc;
	t_tuple			normal;
	double			hit_dist;
	int				clo_obj_id;
	union u_tuple	color;
	t_vector		to_eye;
	t_object		*object;
	int				inside;
	t_vector		reflect_v;
	t_tuple			over_point;
	int				neg_hit;
	size_t			neg_hit_id;
	int				is_shadowed;
	int				normal_disturbance;
}					t_hit_record;

typedef struct s_ray
{
	t_tuple			orig;
	t_tuple			dir;
	t_hit_record	hit;
	t_intersections	xs;
	int				remaining;
}					t_ray;

typedef struct s_intersection
{
	double			t;
	size_t			i;
	t_object		*object;
}					t_intersection;

typedef struct s_light
{
	t_point			location;
	t_vector		direction;
	t_color			intensity;
	int				type;
}					t_light;

typedef struct s_light_params
{
	t_vector		to_light;
	double			distance;
	t_vector		direction;

}					t_light_params;

typedef struct s_negative
{
	double			t[2];
	t_intersection	t1;
	t_intersection	t2;
	size_t			i;
	size_t			j;
}				t_negative;

typedef struct s_lighting
{
	t_color		result;
	t_color		effective_color;
	t_vector	to_light_v;
	t_color		ambient;
	double		light_dot_normal;
	t_color		diffuse;
	t_color		specular;
	t_vector	reflection_v;
	double		reflection_dot_eye;
	double		factor;
}				t_lighting;

t_object			object_new(int shape_type);
double				calc_discriminant(double a, double b, double c);
t_ray				ray_new(t_point origin, t_vector dir);
t_ray				ray_new_malloc(t_point origin, t_vector dir);
t_ray				ray_new_no_malloc(t_point origin, t_vector dir);
void				ray_free(t_ray *ray);
t_point				ray_position(t_ray ray, double t);
int					phere_intersect(t_ray *ray, t_object *s);
t_ray				ray_transform(t_ray *source, t_matrix *transform);
void				intersection_record(t_ray *ray, double time, \
					t_object *s);
void				intersection_record_test(t_ray *ray, double t1, \
					double t2, t_object *s);
int					intersect_sphere(t_ray *inc_ray, t_object *s);
int					intersect_plane(t_ray *inc_ray, t_object *s);
int					intersect_cylinder(t_ray *inc_ray, t_object *s);
int					intersect_cone(t_ray *inc_ray, t_object *s);
t_intersection		intersection_new(double time, t_object *o);
t_intersection		find_closest_intersection(t_intersections *xs);
void				set_transform(t_object *obj, t_matrix *transform);
t_vector			normal_at(t_object *obj, t_point point);
t_material			material_new(void);

void				get_negative_intersects(t_ray *ray, size_t neg_obj_id, \
					t_negative *neg_hits);
size_t				move_negative(t_ray *ray, size_t neg_obj_id, t_negative *n);
int					first_positive_object(t_ray *ray, \
					t_intersection *closest_t, t_negative *n);
void				slice(t_ray *ray, double t1, double t2, t_object *obj);

#endif
