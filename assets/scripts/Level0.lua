Level0 = 
{
    assets = 
    {
        [0] = { type="texture", id = "collision-image", file = "assets/images/collision-texture.png" },
        [1] = { type="texture", id = "tank-image", file = "assets/images/tank-big-right.png" },
        [2] = { type="texture", id = "chopper-image", file = "assets/images/chopper-spritesheet.png" },
        [3] = { type="texture", id = "radar-image", file = "assets/images/radar.png" },
        [4] = { type="texture", id = "jungle-tile", file = "./assets/tilemaps/jungle.png" },
        [5] = { type="texture", id = "heliport-image", file = "assets/images/heliport.png" },
        [6] = { type="texture", id = "projectile", file = "assets/images/bullet-enemy.png" },
        [7] = { type="texture", id = "truck-right-texture", file = "assets/images/truck-right.png" },
        [8] = { type="font", id = "charriot-font", file = "assets/fonts/charriot.ttf", fontSize = 14}
    },

    map = 
    {
        textureAssetID = "jungle-tile",
        file = "assets/tilemaps/jungle.map",
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
                        x = 240,
                        y = 106
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
                    animationSpeed = 90,
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
                        x = 150,
                        y = 495
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
                projectileEmitter = 
                {
                    speed = 70,
                    range = 1000,
                    angle = 270,
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
                        x = 250,
                        y = 495
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
                        x = 243,
                        y = 597
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
        }
    }
}

