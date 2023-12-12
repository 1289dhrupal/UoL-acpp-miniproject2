import json


class RoomObject:
    id: str
    desc: str

    def __init__(self, id, desc):
        self.id = id
        self.desc = desc

    def __str__(self) -> str:
        return self.id

    def get_details(self):
        print(self.id, '->', self.desc)


class Enemy:
    id: str
    desc: str
    aggressiveness: int
    killedby: list
    killed: bool = False

    def __init__(self, id, desc, aggressiveness, killedby=[]):
        self.id = id
        self.desc = desc
        self.aggressiveness = aggressiveness
        self.killedby = killedby

    def __str__(self) -> str:
        return self.id

    def get_details(self):
        print(self.id, ',', self.desc, 'can be killed by',
              ', '.join(self.killedby))

    def can_be_killed(self, weapons: list):
        return bool(set(self.killedby).intersection(set(weapons)))


class Room:
    id: str
    desc: str
    exits: dict
    objects: dict
    enemies: dict

    def __init__(self, id, desc, exits, objects={}, enemies={}):
        self.id = id
        self.desc = desc
        self.exits = exits
        if isinstance(objects, list):
            objects = {
                w.id: w
                for w in objects
            }
        if isinstance(enemies, list):
            enemies = {
                e.id: e
                for e in enemies
            }
        self.objects = objects
        self.enemies = enemies

    def pick(self, obj):
        return self.objects.pop(obj)

    def look(self):
        print(self.desc)
        self.get_all_objects()
        self.get_all_exits()
        self.get_all_enemies()

    def goto(self, exit):
        return self.exits.get(exit, None)

    def get_all_objects(self):
        if not self.objects:
            print('No objects lying around in this room.')
            return
        for _, obj in self.objects.items():
            obj.get_details()

    def get_all_exits(self):
        if not self.exits:
            print("You're trapped!")
            return
        print('Available exits are : -', ', '.join(self.exits.keys()))

    def get_all_enemies(self):
        if not self.enemies:
            print("No enemies in this room")
            return
        for i, enemy in enumerate(self.enemies, 1):
            print(f'{i}.', end='')
            self.look_enemy(enemy)

    def has_enemy(self, enemy):
        if enemy not in self.enemies:
            print('No such enemy')
            return False
        return True

    def look_enemy(self, enemy):
        if self.has_enemy(enemy):
            enemy: Enemy = self.enemies.get(enemy)
            enemy.get_details()

    def can_kill_enemy(self, enemy, weapons: list):
        if self.has_enemy(enemy):
            enemy: Enemy = self.enemies.get(enemy)
            return enemy.can_be_killed(weapons)
        return None

    def kill_enemy(self, enemy, weapon) -> Enemy:
        if not self.has_enemy(enemy):
            return None
        if self.can_kill_enemy(enemy, weapon):
            return self.enemies.pop(enemy)
        return False

    def get_object(self, object_name) -> RoomObject:
        return self.objects.get(object_name, None)

    def has_object(self, object_name) -> bool:
        return object_name in self.objects

    def take_object(self, object_name) -> RoomObject:
        return self.objects.pop(object_name, None)

    def add_object(self, obj: RoomObject) -> RoomObject:
        self.objects[obj.id] = obj

    @property
    def has_exits(self):
        return bool(self.exits)

    @property
    def has_enemies(self):
        return bool(self.enemies)

    def __str__(self):
        return self.id


class Game:
    room: Room
    objective: str
    what: list[str]
    accomplished: list[str]
    rooms: dict[str, Room]
    room_changed = True
    objects_possesed: dict[str, RoomObject]

    @property
    def completed(self):
        return bool(set(self.what)-set(self.accomplished))

    @property
    def failed(self):
        return not self.room.has_exits

    def game_over(self, msg):
        print(msg, 'Game Over ;-(.')
        exit()

    def lookup(self, force=False):
        if self.room_changed or force:
            print("You're now in", game.room)
            self.room_changed = False
            return self.room.look()

    def get_room(self, name):
        return self.rooms.get(name)

    def take_exit(self, exit):
        next_room = self.room.goto(exit)
        if not next_room:
            print('No such exit found!')
            return
        if game.room.has_enemies:
            self.game_over("You're attacked by enemy and died.")
        game.room = self.get_room(next_room)
        self.room_changed = True

    def get_object(self, object_name, default=None) -> RoomObject:
        return self.objects_possesed.get(object_name, default)

    def lookup_object(self, object_name):
        obj = self.get_object(
            object_name,
            self.room.get_object(object_name)
        )
        if not obj:
            print('No such object found.')
        else:
            obj.get_details()

    def take_object(self, object_name):
        if self.room.has_object(object_name):
            self.objects_possesed[object_name] = self.room.take_object(
                object_name
            )
        else:
            print('No such object found.')

    def drop_object(self, object_name):
        if object_name not in self.objects_possesed:
            print('No such object found.')
        else:
            self.room.add_object(
                self.objects_possesed.pop(object_name)
            )

    def list_items(self):
        for i, item in enumerate(self.objects_possesed, 1):
            print(f'{i}.', end=' ')
            self.lookup_object(item)

    def list_enemies(self):
        self.room.get_all_enemies()

    def kill_enemy(self, enemy):
        result = self.room.kill_enemy(enemy, self.objects_possesed.keys())
        if result is not None:
            if not result:
                self.game_over(f"You could not kill {enemy} and died.")
            else:
                print('You killed', result.id)

    def perform_action(self, action, value=None):
        if action == 'look' and not value:
            value = 'around'
        if action == 'exit':
            exit()
        if action == 'look':
            if value == 'around':
                self.lookup(True)
            else:
                self.lookup_object(value)
        elif action == 'go' and value:
            game.take_exit(value)
        elif action == 'list' and value == 'items':
            game.list_items()
        elif action == 'take':
            game.take_object(value)
        elif action == 'drop':
            game.drop_object(value)
        elif action == 'kill':
            game.kill_enemy(value)
        else:
            print('Invalid action')

    def __init__(self, initial_room, type, what, rooms):
        self.type = type
        self.what = what
        self.rooms = rooms
        self.room = rooms[initial_room]
        self.accomplished = []
        self.objects_possesed = {}


data = json.load(open('map3.json', 'r'))
rooms = {}
objects = {}
enemies = {}

for o in data['objects']:
    objects.setdefault(o.pop('initialroom'), []).append(RoomObject(**o))
for e in data['enemies']:
    enemies.setdefault(e.pop('initialroom'), []).append(Enemy(**e))

for r in data['rooms']:
    rooms[r['id']] = Room(
        **r,
        objects=objects.get(r['id'], {}),
        enemies=enemies.get(r['id'], {}),
    )


game = Game(
    data['player']['initialroom'],
    **data['objective'],
    rooms=rooms
)
print('Game started...')
while True:
    if game.failed:
        game.game_over("You're trapped.")

    game.lookup()
    next_move = input("What's your next move? ")
    value = ''
    if ' ' in next_move:
        next_move, value = next_move.split(' ', 1)
    game.perform_action(next_move.strip(), value.strip())


'''
Things that are done
- Navigating rooms
- Picking/Dropping objects along with tracking of their location
- Basic kill commands

'''