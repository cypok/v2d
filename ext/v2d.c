#include <ruby.h>
#include <math.h>

VALUE cV2D;

ID ix, iy;

/* DEFINITIONS */

/*VALUE v2d_initialize(VALUE self);*/
VALUE v2d_initialize_with_x_and_y(VALUE self, VALUE x, VALUE y);
VALUE v2d_square_brackets(VALUE klass, VALUE x, VALUE y);
VALUE v2d_get_x(VALUE self);
VALUE v2d_get_y(VALUE self);
VALUE v2d_set_x(VALUE self, VALUE x);
VALUE v2d_set_y(VALUE self, VALUE y);
VALUE v2d_add(VALUE self, VALUE other);
VALUE v2d_sub(VALUE self, VALUE other);
VALUE v2d_mul(VALUE self, VALUE multiplier);
VALUE v2d_div(VALUE self, VALUE divisor);
VALUE v2d_abs(VALUE self);
VALUE v2d_equals(VALUE self, VALUE other);

void Init_v2d() {
    cV2D = rb_define_class("V2D", rb_cObject);

    /*rb_define_method(cV2D, "initialize", v2d_initialize, 0);*/
    rb_define_method(cV2D, "initialize", v2d_initialize_with_x_and_y, 2);
    rb_define_singleton_method(cV2D, "[]", v2d_square_brackets, 2);
    rb_define_method(cV2D, "x", v2d_get_x, 0);
    rb_define_method(cV2D, "y", v2d_get_y, 0);
    rb_define_method(cV2D, "x=", v2d_set_x, 1);
    rb_define_method(cV2D, "y=", v2d_set_y, 1);
    rb_define_method(cV2D, "+", v2d_add, 1);
    rb_define_method(cV2D, "-", v2d_sub, 1);
    rb_define_method(cV2D, "*", v2d_mul, 1);
    rb_define_method(cV2D, "/", v2d_div, 1);
    rb_define_method(cV2D, "abs", v2d_abs, 0);
    rb_define_method(cV2D, "==", v2d_equals, 1);

    ix = rb_intern("@x");
    iy = rb_intern("@y");
}

/* IMPLEMENTATION */

/*VALUE v2d_initialize(VALUE self) {*/
    /*return self;*/
/*}*/

VALUE v2d_initialize_with_x_and_y(VALUE self, VALUE x, VALUE y) {
    rb_ivar_set(self, ix, x);
    rb_ivar_set(self, iy, y);
    return self;
}

VALUE v2d_square_brackets(VALUE klass, VALUE x, VALUE y) {
    VALUE args[] = {x, y};
    return rb_class_new_instance(2, args, cV2D);
}

VALUE v2d_get_x(VALUE self) {
    return rb_ivar_get(self, ix);
}

VALUE v2d_get_y(VALUE self) {
    return rb_ivar_get(self, iy);
}

VALUE v2d_set_x(VALUE self, VALUE x) {
    return rb_ivar_set(self, ix, x);
}

VALUE v2d_set_y(VALUE self, VALUE y) {
    return rb_ivar_set(self, iy, y);
}

VALUE v2d_add(VALUE self, VALUE other) {
    double left_x = NUM2DBL(rb_ivar_get(self, ix));
    double left_y = NUM2DBL(rb_ivar_get(self, iy));
    double right_x = NUM2DBL(rb_ivar_get(other, ix));
    double right_y = NUM2DBL(rb_ivar_get(other, iy));
    VALUE args[] = {
        rb_float_new(left_x + right_x),
        rb_float_new(left_y + right_y)
    };
    return rb_class_new_instance(2, args, cV2D);
}

VALUE v2d_sub(VALUE self, VALUE other) {
    double left_x = NUM2DBL(rb_ivar_get(self, ix));
    double left_y = NUM2DBL(rb_ivar_get(self, iy));
    double right_x = NUM2DBL(rb_ivar_get(other, ix));
    double right_y = NUM2DBL(rb_ivar_get(other, iy));
    VALUE args[] = {
        rb_float_new(left_x - right_x),
        rb_float_new(left_y - right_y)
    };
    return rb_class_new_instance(2, args, cV2D);
}

VALUE v2d_mul(VALUE self, VALUE multiplier) {
    double left_x = NUM2DBL(rb_ivar_get(self, ix));
    double left_y = NUM2DBL(rb_ivar_get(self, iy));
    double right  = NUM2DBL(multiplier);
    VALUE args[] = {
        rb_float_new(left_x * right),
        rb_float_new(left_y * right)
    };
    return rb_class_new_instance(2, args, cV2D);
}

VALUE v2d_div(VALUE self, VALUE divisor) {
    double left_x = NUM2DBL(rb_ivar_get(self, ix));
    double left_y = NUM2DBL(rb_ivar_get(self, iy));
    double right  = NUM2DBL(divisor);
    VALUE args[] = {
        rb_float_new(left_x / right),
        rb_float_new(left_y / right)
    };
    return rb_class_new_instance(2, args, cV2D);
}

VALUE v2d_abs(VALUE self) {
    double x = NUM2DBL(rb_ivar_get(self, ix));
    double y = NUM2DBL(rb_ivar_get(self, iy));
    return rb_float_new(sqrt(x*x + y*y));
}

VALUE v2d_equals(VALUE self, VALUE other) {
    double left_x = NUM2DBL(rb_ivar_get(self, ix));
    double left_y = NUM2DBL(rb_ivar_get(self, iy));
    double right_x = NUM2DBL(rb_ivar_get(other, ix));
    double right_y = NUM2DBL(rb_ivar_get(other, iy));
    return (left_x == right_x && left_y == right_y) ? Qtrue : Qfalse;
}
