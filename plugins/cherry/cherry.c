#include <stddef.h>
#include <stdlib.h>
#include "../game/game.h"
#include "../score/score.h"
#include "../inventory/inventory.h"

static struct entity cherry_entity;

static bool use_cherry(struct itemstack *stack)
{
	(void) stack;

	add_health(&player, 2);
	return true;
}

static struct item cherry_item = {
	.name = "Cherry",
	.stackable = true,

	.on_use = &use_cherry,
	.on_destroy = NULL,
};

static void cherry_step(struct entity *self, struct entity_step_data stepdata)
{
	if (stepdata.dx == 0 && stepdata.dy == 0) {
		add_score(2);
		inventory_add(&player_inventory, (struct itemstack) {
			.item = &cherry_item,
			.count = 1,
			.meta = NULL,
		});
		self->remove = true;
	}
}

static void spawn_cherry(int x, int y)
{
	spawn(cherry_entity, x, y, NULL);
}

__attribute__((constructor)) static void init()
{
	cherry_entity = (struct entity) {
		.name = "cherry",
		.x = 0,
		.y = 0,
		.color = get_color("#FF2A53"),
		.texture = "🍒",
		.remove = false,
		.meta = NULL,
		.health = 1,
		.max_health = 1,
		.collide_with_entities = false,

		.on_step = &cherry_step,
		.on_collide = NULL,
		.on_collide_with_entity = NULL,
		.on_spawn = NULL,
		.on_remove = NULL,
		.on_death = NULL,
		.on_damage = NULL,
	};

	register_air_function((struct generator_function) {
		.chance = 100,
		.callback = &spawn_cherry,
	});
}

