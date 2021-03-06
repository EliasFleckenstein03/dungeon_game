#include <stdlib.h>
#include <stddef.h>
#include "../game/game.h"
#include "../score/score.h"

struct monster_data
{
	double timer;
};

static void monster_spawn(struct entity *self, void *data)
{
	self->meta = malloc(sizeof(struct monster_data));
	((struct monster_data *) self->meta)->timer = 0.5;
}

static void monster_step(struct entity *self, struct entity_step_data stepdata)
{
	struct monster_data *data = self->meta;

	if (stepdata.visible && (data->timer -= stepdata.dtime) <= 0.0) {
		data->timer = 0.5;

		(stepdata.dx && move(self, stepdata.dx > 0 ? -1 : 1, 0)) || (stepdata.dy && move(self, 0, stepdata.dy > 0 ? -1 : 1));
	}
}

static void monster_collide_with_entity(struct entity *self, struct entity *other)
{
	if (other == &player)
		add_health(other, -1);
}

static void monster_death(struct entity *self)
{
	add_score(5);
	self->remove = true;
}

static struct entity monster_entity = {
	.name = "monster",
	.x = 0,
	.y = 0,
	.color = {0},
	.use_color = false,
	.texture = "👾",
	.remove = false,
	.meta = NULL,
	.health = 5,
	.max_health = 5,
	.collide_with_entities = true,

	.on_step = &monster_step,
	.on_collide = NULL,
	.on_collide_with_entity = &monster_collide_with_entity,
	.on_spawn = &monster_spawn,
	.on_remove = NULL,
	.on_death = &monster_death,
	.on_damage = NULL,
};


static void spawn_monster(int x, int y, enum mg_context ctx)
{
	spawn(monster_entity, x, y, NULL);
}

__attribute__((constructor)) static void init()
{
	register_air_function((struct generator_function) {
		.corridor_chance = 50,
		.room_chance = 200,
		.callback = &spawn_monster,
	});
}
