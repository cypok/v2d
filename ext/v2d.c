#include <ruby.h>
#include <math.h>

VALUE cV2D;

ID ix, iy;

/* DEFINITION */

typedef struct _V2D {
    double x, y;
} V2D;

VALUE v2d_alloc(VALUE klass);
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

    rb_define_alloc_func(cV2D, v2d_alloc);
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

VALUE v2d_alloc(VALUE klass) {
    V2D *v = (V2D *)xmalloc(sizeof(V2D));
    return Data_Wrap_Struct(klass, NULL, xfree, v);
}

/*VALUE v2d_initialize(VALUE self) {*/
    /*return self;*/
/*}*/

VALUE v2d_initialize_with_x_and_y(VALUE self, VALUE x, VALUE y) {
    V2D *v;
    Data_Get_Struct(self, V2D, v);
    v->x = NUM2DBL(x);
    v->y = NUM2DBL(y);
    return self;
}

VALUE v2d_square_brackets(VALUE klass, VALUE x, VALUE y) {
    VALUE args[] = {x, y};
    return rb_class_new_instance(2, args, cV2D);
}

VALUE v2d_get_x(VALUE self) {
    V2D *v;
    Data_Get_Struct(self, V2D, v);
    return rb_float_new(v->x);
}

VALUE v2d_get_y(VALUE self) {
    V2D *v;
    Data_Get_Struct(self, V2D, v);
    return rb_float_new(v->y);
}

VALUE v2d_set_x(VALUE self, VALUE x) {
    V2D *v;
    Data_Get_Struct(self, V2D, v);
    v->x = NUM2DBL(x);
    return x;
}

VALUE v2d_set_y(VALUE self, VALUE y) {
    V2D *v;
    Data_Get_Struct(self, V2D, v);
    v->y = NUM2DBL(y);
    return y;
}

VALUE v2d_add(VALUE self, VALUE other) {
    V2D *v1, *v2;
    Data_Get_Struct(self, V2D, v1);
    Data_Get_Struct(other, V2D, v2);

    V2D *res = (V2D*)xmalloc(sizeof(V2D));
    res->x = v1->x + v2->x;
    res->y = v1->y + v2->y;
    return Data_Wrap_Struct(cV2D, NULL, xfree, res);
}

VALUE v2d_sub(VALUE self, VALUE other) {
    V2D *v1, *v2;
    Data_Get_Struct(self, V2D, v1);
    Data_Get_Struct(other, V2D, v2);

    V2D *res = (V2D*)xmalloc(sizeof(V2D));
    res->x = v1->x - v2->x;
    res->y = v1->y - v2->y;
    return Data_Wrap_Struct(cV2D, NULL, xfree, res);
}

VALUE v2d_mul(VALUE self, VALUE multiplier) {
    V2D *v;
    Data_Get_Struct(self, V2D, v);
    double m = NUM2DBL(multiplier);

    V2D *res = (V2D*)xmalloc(sizeof(V2D));
    res->x = v->x * m;
    res->y = v->y * m;
    return Data_Wrap_Struct(cV2D, NULL, xfree, res);
}

VALUE v2d_div(VALUE self, VALUE divisor) {
    V2D *v;
    Data_Get_Struct(self, V2D, v);
    double d = NUM2DBL(divisor);

    V2D *res = (V2D*)xmalloc(sizeof(V2D));
    res->x = v->x / d;
    res->y = v->y / d;
    return Data_Wrap_Struct(cV2D, NULL, xfree, res);
}

VALUE v2d_abs(VALUE self) {
    V2D *v;
    Data_Get_Struct(self, V2D, v);
    return rb_float_new(sqrt(v->x*v->x + v->y*v->y));
}

VALUE v2d_equals(VALUE self, VALUE other) {
    V2D *v1, *v2;
    Data_Get_Struct(self, V2D, v1);
    Data_Get_Struct(other, V2D, v2);
    return (v1->x == v2->x && v1->y == v2->y) ? Qtrue : Qfalse;
}
