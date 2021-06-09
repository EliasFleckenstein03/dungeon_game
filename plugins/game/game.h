#ifndef _GAME_H_
#define _GAME_H_

#include <stdbool.h>
#define MAP_HEIGHT 1000
#define MAP_WIDTH 1000
#define LIGHT 10

/* Type definitions */

struct color
{
	unsigned char r, g, b;
};

struct material
{
	bool solid;
	struct color color;
};

struct node
{
	struct material *material;
};

struct entity_step_data
{
	double dtime;
	int dx;
	int dy;
	bool visible;
};

struct entity
{
	const char *name;
	int x, y;
	struct color color;
	char texture[8];
	bool remove;
	void *meta;
	int health;
	int max_health;
	bool collide_with_entities;

	void (*on_step)(struct entity *self, struct entity_step_data stepdata);
	void (*on_collide)(struct entity *self, int x, int y);
	void (*on_collide_with_entity)(struct entity *self, struct entity *other);
	void (*on_spawn)(struct entity *self);
	void (*on_remove)(struct entity *self);
	void (*on_death)(struct entity *self);
};

struct list
{
	void *element;
	struct list *next;
};

typedef struct entity *render_entity_list[LIGHT * 2 + 1][LIGHT * 2 + 1];

struct generator_function
{
	int chance;
	void (*callback)(int x, int y);
};

extern int score;

extern struct color black;

extern struct material wall;
extern struct material air;
extern struct material outside;

extern struct node map[MAP_WIDTH][MAP_HEIGHT];

extern struct entity player;
extern struct list *entities;

extern struct entity *entity_collision_map[MAP_WIDTH][MAP_HEIGHT];

extern struct list *air_functions;

void quit();
struct color get_color(const char *str);
bool is_outside(int x, int y);
struct node get_node(int x, int y);
bool is_solid(int x, int y);
bool move(struct entity *entity, int xoff, int yoff);
void spawn(struct entity def, int x, int y);
void add_health(struct entity *entity, int health);
void add_score(int s);
void set_color(struct color color, bool bg);
struct color light_color(struct color color, double light);
void register_air_function(struct generator_function func);
struct list *add_element(struct list *list, void *element);

#endif