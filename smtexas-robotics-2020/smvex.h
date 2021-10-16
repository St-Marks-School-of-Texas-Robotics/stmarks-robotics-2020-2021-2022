#ifndef SMVEX_H
#define SMVEX_H

#define X_AXIS true
#define Y_AXIS false

typedef struct {
    bool left, right, up, down;
} Button;

typedef struct {
    int x_axis, y_axis;
    float x_scale, y_scale;
} Joystick;

typedef struct {
    // Control Axes
    Joystick *Left, *Right;

    // Buttons
    Button btn5, btn6, btn7, btn8;
} Controller;

void loop(Controller *c);
void __update_controller(Controller *c);

void init(Controller *c);

task main() {
    // controller initialization
    Controller _con;

    Joystick _LJ, _RJ;
    _LJ.x_scale = 1;
    _LJ.y_scale = 1;
    _RJ.x_scale = 1;
    _RJ.y_scale = 1;

    _con.Left = &_LJ;
    _con.Right = &_RJ;
    Controller *c = &_con;

    // user initialization
    init(c);

    // main control loop
    while (true) {
        __update_controller(c);

        loop(c);
    }
}

void __update_controller(Controller *c) {
    c->Left->x_axis = vexRT[Ch4];
    c->Left->y_axis = vexRT[Ch3];
    c->Right->x_axis = vexRT[Ch1];
    c->Right->y_axis = vexRT[Ch2];

    c->btn5.up = vexRT[Btn5U] > 0;
    c->btn5.down = vexRT[Btn5D] > 0;

    c->btn6.up = vexRT[Btn6U] > 0;
    c->btn6.down = vexRT[Btn6D] > 0;

    c->btn7.up = vexRT[Btn7U] > 0;
    c->btn7.down = vexRT[Btn7D] > 0;
    c->btn7.left = vexRT[Btn7L] > 0;
    c->btn7.right = vexRT[Btn7R] > 0;

    c->btn8.up = vexRT[Btn8U] > 0;
    c->btn8.down = vexRT[Btn8D] > 0;
    c->btn8.left = vexRT[Btn8L] > 0;
    c->btn8.right = vexRT[Btn8R] > 0;
}

int __get_joystick_value(Joystick *j, bool axis) {
    if (axis) {
        return (int)(j->x_axis * j->x_scale);
    }

    return (int)(j->y_axis * j->y_scale);
}

void map_linear(Joystick *j, bool axis, int port) {
    motor[port] = __get_joystick_value(j, axis);
}

void map_threshold(Joystick *j, bool axis, int threshold, int port) {
    int value;
    float scale;
    if (axis) {
        value = j->x_axis;
        scale = j->x_scale;
    } else {
        value = j->y_axis;
        scale = j->y_scale;
    }

    if (abs(value) > threshold) {
        motor[port] = (int)(value / abs(value) * 127 * scale);
    } else {
        motor[port] = 0;
    }
}

#define __PivThreshold 64.0

void drive_control_from_scaled(Joystick *j, int lport, int rport, float lscale, float rscale) {
    int x = j->x_axis * j->x_scale, y = j->y_axis * j->y_scale;

    // calculate the base (unscaled) values for the forward motor outputs
    float motorlf_base, motorrf_base;
    if (y >= 0) {
        // forward
        motorlf_base = x < 0 ? 127 + x : 127;
        motorrf_base = x < 0 ? 127 : 127 + x;
    } else {
        // reverse
        motorlf_base = x < 0 ? 127 : 127 + x;
        motorrf_base = x < 0 ? 127 + x : 127;
    }

    // scale the motor outputs (throttle)
    motorlf_base *= y/128.0;
    motorrf_base *= y/128.0;

    // calculate the pivot (0 if no scale, > 0 if should scale)
    float piv_scale = abs(y) > __PivThreshold ? 0.0 : 1.0-abs(y)/__PivThreshold;

    // apply the pivot to calculate the final forward motor outputs
    float motorlf_out = (1 - piv_scale) * motorlf_base + piv_scale * x,
        motorrf_out = (1 - piv_scale) * motorrf_base + piv_scale * -x;

    motor[lport] = (int)(motorlf_out * lscale);
    motor[rport] = (int)(motorrf_out * rscale);
}

void drive_control_from(Joystick *j, int lport, int rport) {
    drive_control_from_scaled(j, lport, rport, 1.0, 1.0);
}

#endif
