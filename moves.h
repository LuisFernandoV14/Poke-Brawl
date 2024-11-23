#ifndef moves_h
#define moves_h

// Estrutura do ataque
typedef struct {
    char nome[50];         // Nome do ataque
    char tipo[20];         // Tipo do ataque (Fogo, Água, etc.)
    int pp;                // Pontos de poder (PP)
    int categoria;         // 0 (Físico), 1 (Especial)
    int poder;             // Poder do ataque
    int prioridade;        // Prioridade do ataque
    int accuracy;          // Precisão do ataque (0-100)
    int critico;           // Multiplicador de chance de crítico
} move;

// Declaração dos ataques de Emboar
move scald = {"Scald", "água", 15, 1, 80, 0, 100, 1};        
move blast_burn = {"Blast Burn", "fogo", 5, 1, 150, 0, 90, 1}; 
move roar = {"Roar", "normal", 20, 0, 0, 0, 100, 1};         
move arm_thrust = {"Arm Thrust", "luta", 20, 0, 15, 0, 100, 1}; 

// Declaração dos ataques de Dragonite
move outrage = {"Outrage", "dragão", 10, 0, 120, 0, 100, 1};     
move aqua_tail = {"Aqua Tail", "água", 10, 0, 90, 0, 90, 1};      
move wing_attack = {"Wing Attack", "voador", 35, 0, 60, 0, 100, 1}; 
move air_cutter = {"Air Cutter", "voador", 25, 1, 60, 0, 95, 2};   

//Declaração dos ataques de Golurk
move high_horsepower = {"High Horsepower", "terra", 10, 0, 95, 0, 95, 1}; 
move shadow_ball = {"Shadow Ball", "fantasma", 15, 1, 80, 0, 100, 1};         
move earth_power = {"Earth Power", "terra", 10, 1, 90, 0, 100, 1};       
move protect = {"Protect", "normal", 10, 0, 0, 4, 0, 1};                     

//Declaração dos Ataques de Salamence
move fly = {"Fly", "voador", 15, 0, 90, 0, 95, 1};                
// move outrage = {"Outrage", "dragão", 10, 0, 120, 0, 100, 1};      
move giga_impact = {"Giga Impact", "normal", 5, 0, 150, 0, 90, 1}; 
move dual_wingbeat = {"Dual Wingbeat", "voador", 15, 0, 40, 0, 90, 1}; 

// Declaração dos Ataques de Lapras
move hydro_pump = {"Hydro Pump", "água", 5, 1, 110, 0, 80, 1};      
move blizzard = {"Blizzard", "gelo", 5, 1, 110, 0, 70, 1};        
move body_slam = {"Body Slam", "normal", 15, 0, 85, 0, 100, 1};     
move whirlpool = {"Whirlpool", "água", 15, 1, 35, 0, 85, 1};       

//Declaração dos Ataques de Pidgeot
move mirror_move = {"Mirror Move", "voador", 15, 0, 0, 0, 100, 1}; 
move u_turn = {"U-turn", "inseto", 20, 0, 70, 0, 100, 1};          
move quick_attack = {"Quick Attack", "normal", 30, 0, 40, 1, 100, 1}; 
move tailwind = {"Tailwind", "voador", 20, 0, 0, 0, 100, 1};       

// Declaração dos Ataques de Muk
move toxic = {"Toxic", "veneno", 10, 0, 0, 0, 90, 1};            
move sludge_bomb = {"Sludge Bomb", "veneno", 10, 1, 90, 0, 100, 1}; 
move acid_armor = {"Acid Armor", "veneno", 20, 0, 0, 0, 100, 1};  
//move giga_impact = {"Giga Impact", "normal", 5, 0, 150, 0, 90, 1};  

// Declaração dos Ataques de Alakazam
move future_sight = {"Future Sight", "psíquico", 10, 1, 120, 0, 100, 1}; 
move speed_swap = {"Speed Swap", "psíquico", 10, 0, 0, 0, 100, 1};        
move zen_headbutt = {"Zen Headbutt", "psíquico", 15, 0, 80, 0, 90, 1};    
move psycho_cut = {"Psycho Cut", "psíquico", 15, 0, 70, 0, 100, 2};      

//Declaração dos Ataques de Tyranitar
move stealth_rock = {"Stealth Rock", "pedra", 10, 0, 0, 0, 100, 1};   
move payback = {"Payback", "sombrio", 10, 0, 50, 0, 100, 1};          
move sand_tomb = {"Sand Tomb", "terra", 15, 0, 35, 0, 85, 1};      
move crunch = {"Crunch", "sombrio", 15, 0, 80, 0, 100, 1};            

//Declaração dos Ataques de Metagross
move metal_claw = {"Metal Claw", "ferro", 15, 0, 50, 0, 95, 1};         
move psyshock = {"Psyshock", "psíquico", 10, 1, 80, 0, 100, 1};        
move steel_beam = {"Steel Beam", "ferro", 5, 1, 140, 0, 95, 1};         
move meteor_mash = {"Meteor Mash", "ferro", 15, 0, 90, 0, 90, 1};       

//Declaração dos Ataques de Greninja
move water_shuriken = {"Water Shuriken", "água", 15, 1, 15, 0, 100, 1}; 
move cut = {"Cut", "normal", 30, 0, 50, 0, 95, 1};                   
move aerial_ace = {"Aerial Ace", "voador", 20, 0, 60, 0, 100, 1};     
move double_team = {"Double Team", "normal", 15, 0, 0, 0, 100, 1};    

//Declaração dos Ataques de Pinsir
move x_scissor = {"X-Scissor", "inseto", 15, 0, 80, 0, 100, 1};       
move false_swipe = {"False Swipe", "normal", 10, 0, 40, 0, 100, 1};    
move dig = {"Dig", "terra", 10, 0, 80, 0, 100, 1};               
move bulk_up = {"Bulk Up", "luta", 20, 0, 0, 0, 100, 1};           

//Declaração dos Ataques de Electivire
move thunder = {"Thunder", "elétrico", 10, 1, 110, 0, 70, 1};         
move thunder_wave = {"Thunder Wave", "elétrico", 20, 0, 0, 0, 90, 1};  
move thunder_punch = {"Thunder Punch", "elétrico", 15, 0, 75, 0, 100, 1}; 
move supercell_slam = {"Supercell Slam", "elétrico", 5, 0, 100, 0, 95, 1}; 

//Declaração dos Ataques de Primarina
move chilling_water = {"Chilling Water", "água", 15, 1, 50, 0, 100, 1}; 
move draining_kiss = {"Draining Kiss", "fada", 15, 1, 50, 0, 100, 1};   
move moonblast = {"Moonblast", "fada", 15, 1, 95, 0, 100, 1};         
move aqua_jet = {"Aqua Jet", "água", 30, 0, 40, 1, 100, 1};           

//Declaração dos Ataques de Honchkrow
//move u_turn = {"U-turn", "inseto", 20, 0, 70, 0, 100, 1};             
move night_shade = {"Night Shade", "fantasma", 15, 1, 0, 0, 100, 1};    
move heat_wave = {"Heat Wave", "fogo", 5, 1, 95, 0, 90, 1};            
move confuse_ray = {"Confuse Ray", "fantasma", 10, 1, 0, 0, 100, 1};    

//Declaração dos Ataques de Chandelure
move substitute = {"Substitute", "normal", 10, 0, 0, 0, 100, 1};      
//move shadow_ball = {"Shadow Ball", "fantasma", 15, 1, 80, 0, 100, 1};  
move flamethrower = {"Flamethrower", "fogo", 15, 1, 90, 0, 100, 1};    
move fire_spin = {"Fire Spin", "fogo", 15, 1, 35, 0, 85, 1};          

//Declaração dos Ataques de Espeon
move psych_up = {"Psych Up", "normal", 15, 1, 0, 0, 100, 1};           
move charm = {"Charm", "fada", 20, 0, 0, 0, 100, 1};                  
//move draining_kiss = {"Draining Kiss", "fada", 15, 1, 50, 0, 100, 1};  
//move body_slam = {"Body Slam", "normal", 15, 0, 85, 0, 100, 1};        


//Declaração dos Ataques de Cubone
move Bonemerang = {"Bonemerang", "terra", 10, 0, 50, 0, 90, 1};
move Dig = {"Dig", "terra", 10, 0, 80, 0, 100, 1};
move Earthquake = {"Earthquake", "terra", 10, 0, 100, 0, 100, 1};
move Sandstorm = {"Sandstorm", "pedra", 10, 2, 0, 0, 0, 0};

//Declaração dos Ataques de Ninetales de Alola
move AuroraVeil = {"Aurora Veil", "gelo", 20, 2, 0, 0, 0, 0};
move FreezeDry = {"Freeze-Dry", "gelo", 10, 1, 70, 0, 100, 1};
move Hypnosis = {"Hypnosis", "psíquico", 20, 2, 0, 0, 60, 1};
move Hail = {"Hail", "gelo", 10, 2, 0, 0, 0, 0};

//Declaração dos Ataques de Purugly
move FakeOut = {"Fake Out", "normal", 10, 0, 40, 3, 100, 1};
move BodySlam = {"Body Slam", "normal", 15, 0, 85, 0, 100, 1};
move SuckerPunch = {"Sucker Punch", "sombrio", 5, 0, 70, 1, 100, 1};
move UTurn = {"U-turn", "inseto", 20, 0, 70, 0, 100, 1};

//Declaração dos Ataques de Nidoking
move SludgeWave = {"Sludge Wave", "veneno", 10, 1, 95, 0, 100, 1};
move EarthPower = {"Earth Power", "terra", 10, 1, 90, 0, 100, 1};
move IceBeam = {"Ice Beam", "gelo", 10, 1, 90, 0, 100, 1};
move Substitute = {"Substitute", "normal", 10, 2, 0, 0, 0, 0};

//Declaração dos Ataques de Venusaur
move Growth = {"Growth", "normal", 40, 2, 0, 0, 0, 0};
move SludgeBomb = {"Sludge Bomb", "veneno", 10, 1, 90, 0, 100, 1};
move GigaDrain = {"Giga Drain", "grama", 10, 1, 75, 0, 100, 1};
move BulletSeed = {"Bullet Seed", "grama", 30, 0, 25, 0, 100, 1};

//Declaração dos Ataques de Charizard
//move Substitute = {"Substitute", "normal", 10, 2, 0, 0, 0, 0};
move BreakingSwipe = {"Breaking Swipe", "dragão", 5, 0, 60, 0, 100, 1};
move Hurricane = {"Hurricane", "voador", 10, 1, 110, 0, 70, 1};
//move Earthquake = {"Earthquake", "terra", 10, 0, 100, 0, 100, 1};

//Declaração dos Ataques de Gallade
move SwordsDance = {"Swords Dance", "normal", 20, 2, 0, 0, 0, 0};
move DrainPunch = {"Drain Punch", "luta", 10, 0, 75, 0, 100, 1};
move PsychoCut = {"Psycho Cut", "psíquico", 10, 0, 70, 0, 100, 2};
move LeafBlade = {"Leaf Blade", "grama", 10, 0, 90, 0, 100, 2};

//Declaração dos Ataques de Gardevoir
move HealPulse = {"Heal Pulse", "psíquico", 10, 2, 0, 0, 0, 0};
move Psyshock = {"Psyshock", "psíquico", 10, 1, 80, 0, 100, 1};
move Moonblast = {"Moonblast", "fada", 10, 1, 95, 0, 100, 1};
move CalmMind = {"Calm Mind", "psíquico", 40, 2, 0, 0, 0, 0};

//Declaração dos Ataques de Magneton
move Thunderbolt = {"Thunderbolt", "elétrico", 10, 1, 90, 0, 100, 1};
move GyroBall = {"Gyro Ball", "ferro", 5, 0, 0, 0, 100, 1};
move FlashCannon = {"Flash Cannon", "ferro", 10, 1, 80, 0, 100, 1};
move VoltSwitch = {"Volt Switch", "elétrico", 10, 1, 70, 0, 100, 1};

//Declaração dos Ataques de Decidueye
move NastyPlot = {"Nasty Plot", "sombrio", 20, 2, 0, 0, 0, 0};
move ShadowBall = {"Shadow Ball", "fantasma", 10, 1, 80, 0, 100, 1};
move LeafStorm = {"Leaf Storm", "grama", 5, 1, 130, 0, 90, 1};
move Roost = {"Roost", "voador", 10, 2, 0, 0, 0, 0};

//Declaração dos Ataques de Umbreon
move Wish = {"Wish", "normal", 10, 2, 0, 0, 0, 0};
move Protect = {"Protect", "normal", 10, 2, 0, 4, 0, 0};
move FoulPlay = {"Foul Play", "sombrio", 10, 0, 95, 0, 100, 1};
//move BodySlam = {"Body Slam", "normal", 15, 0, 85, 0, 100, 1};

//Declaração dos Ataques de Leavanny
move StruggleBug = {"Struggle Bug", "inseto", 20, 1, 50, 0, 100, 1};
//move LeafBlade = {"Leaf Blade", "grama", 15, 0, 90, 0, 100, 2};
move XScissor = {"X-Scissor", "inseto", 15, 0, 80, 0, 100, 1};
//move LeafStorm = {"Leaf Storm", "grama", 5, 1, 130, 0, 90, 1};

//Declaração dos Ataques de Lucario
//move SwordsDance = {"Swords Dance", "normal", 20, 2, 0, 0, 0, 0};
move MeteorMash = {"Meteor Mash", "ferro", 10, 0, 90, 0, 90, 1};
move CloseCombat = {"Close Combat", "luta", 5, 0, 120, 0, 100, 1};
move BulletPunch = {"Bullet Punch", "ferro", 20, 0, 40, 1, 100, 1};

#endif
