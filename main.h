enum{
    OFF = 0,
    RED = 1,
    GREEN = 2,
    BLUE = 3,
    YELLOW = 4,
    MAGENTA = 5,
    CYAN = 6,
    WHITE = 7
    };
    
typedef struct{
        
    uint16_t ID;
    uint16_t dir_L;
    float pwm_L;
    uint16_t dir_R;
    float pwm_R;
    uint16_t led;
    
    }dataIN;
    
