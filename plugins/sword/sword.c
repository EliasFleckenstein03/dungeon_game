#include <stdlib.h>
#include <stddef.h>
#include "../game/game.h"
#include "../movement/movement.h"
#include "../inventory/inventory.h"
#include "../recharge/recharge.h"
#include "../loot/loot.h"

static bool use_broken_sword(struct itemstack *stack)
{
	return true;
}

static struct item broken_sword = {
	.name = "Broken Sword",
	.stackable = false,

	.on_use = &use_broken_sword,
	.on_destroy = NULL,
	.on_create = NULL,
};

static bool use_sword(struct itemstack *stack)
{
	if (! is_charged())
		return false;

	int x, y;
	x = player.x;
	y = player.y;

	dir_to_xy(last_player_move, &x, &y);

	struct entity *entity = entity_collision_map[x][y];

	if (entity) {
		add_health(entity, -1);

		if (rand() % 100 == 0)
			stack->item = &broken_sword;

		recharge(1.0, "⚔ ");
	}

	return false;
}

static struct item sword = {
	.name = "Sword",
	.stackable = false,

	.on_use = &use_sword,
	.on_destroy = NULL,
	.on_create = NULL,
};

static void handle_e()
{
	struct itemstack *stack = inventory_find(&player_inventory, &sword);

	if (stack)
		use_sword(stack);
}

__attribute__((constructor)) static void init()
{
	inventory_add(&player_inventory, (struct itemstack) {
		.item = &sword,
		.count = 1,
		.meta = NULL,
	});

	register_input_handler('e', (struct input_handler) {
		.run_if_dead = false,
		.callback = &handle_e,
	});

	register_loot((struct loot) {
		.chance = 7,
		.item = &sword,
		.min = 1,
		.max = 1,
	});
}
