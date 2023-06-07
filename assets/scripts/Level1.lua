-- Define a table with the start values of the first level
Level = {
    ----------------------------------------------------
    -- Table to define the list of assets
    ----------------------------------------------------
    assets = {
        [0] =
        { type = "texture", id = "parachute-open",            file = "./assets/images/open.png" },
        { type = "texture", id = "parachute-close",            file = "./assets/images/close.png" },
        { type = "font"   , id = "pico8-font-10",           file = "./assets/fonts/pico8.ttf", font_size = 10 }
    },  
    animations = {
    },
    ----------------------------------------------------
    -- table to define the map config variables
    ----------------------------------------------------
    tilemap = {},
    -- tilemap = {
    --     map_file = "./assets/tilemaps/worms.map",
    --     texture_asset_id = "tilemap-beach-soil",
    --     num_rows = 25,
    --     num_cols = 25,
    --     tile_size = 32,
    --     scale = 1.0,
    --     group = "terrain"
    -- },

        ----------------------------------------------------
    -- table to define entities and their components
    ----------------------------------------------------
    entities = {
        [0] =
        {
            -- Player
            tag = "player",
            components = {
                transform = {
                    position = { x = 750, y = 450 },
                    scale = { x = 0.25, y = 0.25 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 },
                    mass = 1.0,
                },
                sprite = {
                    texture_asset_id = "parachute-close",
                    width = 431,
                    height = 431,
                    z_index = 6,
                    fixed = false,
                    src_rect_x = 0,
                    src_rect_y = 0
                },
                boxcollider = {
                    width = 32,
                    height = 25,
                    offset = { x = 0, y = 5 }
                },
                health = {§
                    health_percentage = 100
                },
                keyboard_controller = {
                    up_velocity = { x = 0, y = -30 },
                    right_velocity = { x = 30, y = 0 },
                    down_velocity = { x = 0, y = 30 },
                    left_velocity = { x = -30, y = 0 }
                },
                camera_follow = {
                    follow = true
                },
                force = {

                },
                on_update_script = {
                    [0] =
                    function(entity, delta_time, ellapsed_time)
                        -- force_clear_force(entity);
                        assetId = get_assetId(entity);
                        if assetId == "parachute-open" then
                            -- Print("open");
                            force_clear_force(entity);
                            -- velocity shuld change to 0 in oreder to stop 
                            force_add_force(entity , 0 , -4);
                        end
                        if assetId == "parachute-close" then
                            -- Print("close");
                            force_clear_force(entity);
                            force_add_force(entity , 0 , 9.8);
                        end
                    end
                }
            }
        },
    },
}


-- Define some useful global variables
-- map_width = Level.tilemap.num_cols * Level.tilemap.tile_size * Level.tilemap.scale
-- map_height = Level.tilemap.num_rows * Level.tilemap.tile_size * Level.tilemap.scale
