#include <ruby.h>
#include "v2d.h"

VALUE cV2D;

ID ix, iy;

// DEFINITIONS

/* Allocate memory */
VALUE rb_alloc(VALUE klass);

/* Return new with initialized x and y */
VALUE rb_initialize_with_x_and_y(VALUE self, VALUE x, VALUE y);

/* Return <tt>V2D.new(x, y)</tt> */
VALUE rb_square_brackets(VALUE klass, VALUE x, VALUE y);

/* Return x */
VALUE rb_get_x(VALUE self);

/* Return y */
VALUE rb_get_y(VALUE self);

/* Set x */
VALUE rb_set_x(VALUE self, VALUE x);

/* Set y */
VALUE rb_set_y(VALUE self, VALUE y);

/* Return sum with +other+ */
VALUE rb_add(VALUE self, VALUE other);

/* Return diff with +other+ */
VALUE rb_sub(VALUE self, VALUE other);

/* Return product with +multiplier+ */
VALUE rb_mul(VALUE self, VALUE multiplier);

/* Return quotient with +divisor+ */
VALUE rb_div(VALUE self, VALUE divisor);

/* Return absolute value */
VALUE rb_abs(VALUE self);

/* Return whether equals to +other+ */
VALUE rb_equals(VALUE self, VALUE other);


void Init_v2d() {
    /* 2D vector */
    cV2D = rb_define_class("V2D", rb_cObject);

    rb_define_alloc_func(cV2D, rb_alloc);
    rb_define_method(cV2D, "initialize", rb_initialize_with_x_and_y, 2);
    rb_define_singleton_method(cV2D, "[]", rb_square_brackets, 2);
    rb_define_method(cV2D, "x", rb_get_x, 0);
    rb_define_method(cV2D, "y", rb_get_y, 0);
    rb_define_method(cV2D, "x=", rb_set_x, 1);
    rb_define_method(cV2D, "y=", rb_set_y, 1);
    rb_define_method(cV2D, "+", rb_add, 1);
    rb_define_method(cV2D, "-", rb_sub, 1);
    rb_define_method(cV2D, "*", rb_mul, 1);
    rb_define_method(cV2D, "/", rb_div, 1);
    rb_define_method(cV2D, "abs", rb_abs, 0);
    rb_define_method(cV2D, "==", rb_equals, 1);

    ix = rb_intern("@x");
    iy = rb_intern("@y");
}

// IMPLEMENTATIONS

VALUE rb_alloc(VALUE klass) {
    V2D *v = v2d_new();
    return Data_Wrap_Struct(klass, NULL, v2d_delete, v);
}

VALUE rb_initialize_with_x_and_y(VALUE self, VALUE x, VALUE y) {
    V2D *v;
    Data_Get_Struct(self, V2D, v);
    v->x = NUM2DBL(x);
    v->y = NUM2DBL(y);
    return self;
}

VALUE rb_square_brackets(VALUE klass, VALUE x, VALUE y) {
    VALUE args[] = {x, y};
    return rb_class_new_instance(2, args, cV2D);
}

VALUE rb_get_x(VALUE self) {
    V2D *v;
    Data_Get_Struct(self, V2D, v);
    return rb_float_new(v->x);
}

VALUE rb_get_y(VALUE self) {
    V2D *v;
    Data_Get_Struct(self, V2D, v);
    return rb_float_new(v->y);
}

VALUE rb_set_x(VALUE self, VALUE x) {
    V2D *v;
    Data_Get_Struct(self, V2D, v);
    v->x = NUM2DBL(x);
    return x;
}

VALUE rb_set_y(VALUE self, VALUE y) {
    V2D *v;
    Data_Get_Struct(self, V2D, v);
    v->y = NUM2DBL(y);
    return y;
}

VALUE rb_add(VALUE self, VALUE other) {
    V2D *v1, *v2;
    Data_Get_Struct(self, V2D, v1);
    Data_Get_Struct(other, V2D, v2);
    V2D *res = v2d_add(v1, v2);
    return Data_Wrap_Struct(cV2D, NULL, xfree, res);
}

VALUE rb_sub(VALUE self, VALUE other) {
    V2D *v1, *v2;
    Data_Get_Struct(self, V2D, v1);
    Data_Get_Struct(other, V2D, v2);
    V2D *res = v2d_sub(v1, v2);
    return Data_Wrap_Struct(cV2D, NULL, xfree, res);
}

VALUE rb_mul(VALUE self, VALUE multiplier) {
    V2D *v;
    Data_Get_Struct(self, V2D, v);
    double m = NUM2DBL(multiplier);
    V2D *res = v2d_mul(v, m);
    return Data_Wrap_Struct(cV2D, NULL, xfree, res);
}

VALUE rb_div(VALUE self, VALUE divisor) {
    V2D *v;
    Data_Get_Struct(self, V2D, v);
    double d = NUM2DBL(divisor);
    V2D *res = v2d_div(v, d);
    return Data_Wrap_Struct(cV2D, NULL, xfree, res);
}

VALUE rb_abs(VALUE self) {
    V2D *v;
    Data_Get_Struct(self, V2D, v);
    double res = v2d_abs(v);
    return rb_float_new(res);
}

VALUE rb_equals(VALUE self, VALUE other) {
    V2D *v1, *v2;
    Data_Get_Struct(self, V2D, v1);
    Data_Get_Struct(other, V2D, v2);
    return v2d_equals(v1, v2) ? Qtrue : Qfalse;
}

