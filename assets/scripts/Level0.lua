-- Get current time of day from OS
math.randomseed(os.time())
local currentSystemHour = os.date("*t").hour
local mapTextureAssetID = "forest-tile-day"

-- Use night-map or day-map texture (10am-10pm)
if currentSystemHour >= 10 and currentSystemHour < 22 then
    mapTextureAssetID = "forest-tile-day"
else
    mapTextureAssetID = "forest-tile-night"
end

Level0 = 
{
    assets = 
    {
        [0] = { type="texture", id = "collision-image", file = "assets/images/collision-texture.png" },
        [1] = { type="texture", id = "tank-image", file = "assets/images/tank-big-right.png" },
        [2] = { type="texture", id = "chopper-image", file = "assets/images/chopper-spritesheet.png" },
        [3] = { type="texture", id = "radar-image", file = "assets/images/radar.png" },
        [4] = { type="texture", id = "forest-tile-day", file = "./assets/tilemaps/forest.png" },
        [5] = { type="texture", id = "forest-tile-night", file = "./assets/tilemaps/forest-night.png" },
        [6] = { type="texture", id = "heliport-image", file = "assets/images/heliport.png" },
        [7] = { type="texture", id = "projectile", file = "assets/images/bullet.png" },
        [8] = { type="texture", id = "truck-right-texture", file = "assets/images/truck-right.png" },
        [9] = { type="sound", id = "helicopter-SFX", file = "assets/sounds/helicopter.wav" },
        [10] = { type="font", id = "charriot-font", file = "assets/fonts/charriot.ttf", fontSize = 14}
    },

    map = 
    {
        textureAssetID = mapTextureAssetID,
        file = "assets/tilemaps/forest.map",
        scale = 3,
        tileSize = 32,
        mapSizeX = 25,
        mapSizeY = 20
    },

    entities = 
    {
        -- Player
        [0] = 
        {
            name = "player",
            layer = 4,
            
            components = 
            {
                transform = 
                {
                    position = 
                    {
                        x = 360,
                        y = 170
                    },
                    velocity = 
                    {
                        x = 0,
                        y = 0
                    },
                    width = 32,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = 
                {
                    textureAssetID = "chopper-image",
                    animated = true,
                    hasDirections = true,
                    fixed = false,
                    frameCount = 2,
                    animationSpeed = 90
                },
                collider = { },
                input = 
                {
                    keyboard = 
                    {
                        up = "w",
                        right = "d",
                        down = "s",
                        left = "a",
                        shoot = "space"
                    }
                },
                audio = { 
                    filePath = "assets/sounds/helicopter.wav",
                    playOnAwake = true,
                    isLooping = true
                }
            }
        },

        -- Enemy tank
        [1] = 
        {
            name = "tank",
            layer = 3,
            components = 
            {
                transform = 
                {
                    position = 
                    {
                        x = 650,
                        y = 605
                    },
                    velocity = 
                    {
                        x = 0,
                        y = 0
                    },
                    width = 32,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = 
                {
                    textureAssetID = "tank-image",
                    animated = false
                },
                collider = { },
                emitter = 
                {
                    speed = 70,
                    range = 1000,
                    angle = math.random(360),
                    width = 4,
                    height = 4,
                    shouldLoop = true,
                    textureAssetID = "projectile"
                }
            }
        },

        -- Heliport
        [2] = 
        {
            name = "heliport",
            layer = 3,
            components = 
            {
                transform = 
                {
                    position = 
                    {
                        x = 550,
                        y = 745
                    },
                    velocity = 
                    {
                        x = 0,
                        y = 0
                    },
                    width = 32,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = 
                {
                    textureAssetID = "heliport-image",
                    animated = false
                },
                collider = { }
            }
        },

        -- Truck
        [3] = {
            name = "truck1",
            layer = 3,
            components = 
            {
                transform = 
                {
                    position = 
                    {
                        x = 343,
                        y = 737
                    },
                    velocity = 
                    {
                        x = 0,
                        y = 0
                    },
                    width = 32,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = 
                {
                    textureAssetID = "truck-right-texture",
                    animated = false
                },
                collider = { }
            }
        },

        -- Truck
        [4] = {
            name = "radar",
            layer = 5,
            components = 
            {
                transform = 
                {
                    position = 
                    {
                        x = 1800,
                        y = 15
                    },
                    velocity = 
                    {
                        x = 0,
                        y = 0
                    },
                    width = 64,
                    height = 64,
                    scale = 1,
                    rotation = 0
                },
                sprite = 
                {
                    textureAssetID = "radar-image",
                    animated = true,
                    hasDirections = false,
                    fixed = true,
                    frameCount = 8,
                    animationSpeed = 150
                },
                collider = { }
            }
        },

        -- Text
        [5] = {
            name = "text",
            layer = 5,
            components = 
            {
                label = 
                {
                    position = 
                    {
                        x = 15,
                        y = 15
                    },
                    text = "Welcome to the Qore Engine!",
                    fontFamily = "charriot-font",
                    color =
                    {
                        r = 255,
                        g = 255,
                        b = 255
                    }
                }
            }
        }
    }
}

