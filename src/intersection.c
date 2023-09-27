#include <stdio.h>
#include <stdlib.h>
#include "float.h"
#include "intersection.h"

void intersects_init(Intersects *xs)
{
    xs->len = 0;
    xs->head = NULL;
}

void intersects_add(Intersects *xs, f64 t, const Object *object)
{
    Intersect i = { t, object };
    intersects_push(xs, i);
}

void intersects_push(Intersects *xs, Intersect x)
{
    xs->len++;

    Xsn *next = malloc(sizeof(Xsn));
    next->x = x;

    if (!xs->head || xs->head->x.t > x.t) {
        next->next = xs->head;
        xs->head = next;
    } else {
        Xsn *ptr = xs->head;
        while (ptr->next != NULL && ptr->next->x.t < x.t ) {
            ptr = ptr->next;
        }
        next->next = ptr->next;
        ptr->next = next;
    }
}

void intersects_merge(Intersects *xs, const Intersects *other)
{
    Xsn *n = other->head;
    while (n != NULL) {
        intersects_push(xs, n->x);
        n = n->next;
    }
}

Intersects intersects(int n, ...)
{
    Intersects xs;
    intersects_init(&xs);

    va_list ptr;
    va_start(ptr, n);
    for (size_t i = 0; i < n; ++i) {
        intersects_push(&xs, va_arg(ptr, Intersect));
    }
    va_end(ptr);

    return xs;
}

Intersect* intersects_get(const Intersects *xs, size_t index)
{
    size_t i = 0;
    Xsn *ptr = xs->head;
    while (ptr != NULL) {
        if (i == index) {
            return &ptr->x;
        }
        ptr = ptr->next;
        ++i;
    }
    return NULL;
}

Intersect* intersect_hit(const Intersects *xs)
{
    if (xs->len == 0) {
        return NULL;
    }

    Xsn *ptr = xs->head;
    while (ptr != NULL && ptr->x.t < 0) 
        ptr = ptr->next;

    if (ptr != NULL) {
        return &ptr->x;
    } else {
        return NULL;
    }
}

Color intersect_shade_hit(const World *w, const IntersectPrecomp *comp)
{
    Color c = color(1, 1, 1);
    for (size_t i = 0; i < w->lights.len; ++i) {
        PointLight *light = &w->lights.objects[i];
        bool shadowed = world_is_shadowed(w, i, &comp->over_point);
        Color shade =  material_lighting(&comp->object->material, light, &comp->over_point, &comp->eyev, &comp->normalv, shadowed);
        c = tuple_prod(&c, &shade);
    }
    return c;
}

bool intersect_equal(const Intersect *a, const Intersect *b)
{
    return a->t == b->t && a->object == b->object;
}

void intersects_destroy(Intersects *xs)
{
    Xsn *ptr = xs->head;
    Xsn *next;
    while (ptr != NULL) {
        next = ptr->next;
        free(ptr);
        ptr = next;
    }
    xs->head = NULL;
}

IntersectPrecomp intersect_precomp(const Intersect *i, const Ray *r)
{
    IntersectPrecomp comp = {0};
    comp.t = i->t;
    comp.object = i->object;
    comp.point = ray_position(r, comp.t);
    comp.eyev = tuple_neg(&r->direction);
    comp.normalv = sphere_normal_at(comp.object, &comp.point);
    if (tuple_dot(&comp.normalv, &comp.eyev) < 0) {
        comp.inside = true;
        comp.normalv = tuple_neg(&comp.normalv);
    } else {
        comp.inside = false;
    }
    Vec4 norm_e = tuple_mul(&comp.normalv, EPSILON);
    comp.over_point = tuple_add(&comp.point, &norm_e);
    return comp;
}

Intersects intersect_sphere(const Sphere *s, const Ray *r)
{
    Transform inverse = mat4_invert(&s->transform);
    Ray tr = ray_transform(r, &inverse);
    size_t result = 0;

    Intersects inters;
    intersects_init(&inters);

    /* Ray from sphere center to ray origin */
    Vec4 origin = ORIGIN;
    Vec4 s_to_r = tuple_sub(&tr.origin, &origin);

    /* Calculate discriminant */
    f64 a = tuple_dot(&tr.direction, &tr.direction);
    f64 b = 2.0 * tuple_dot(&tr.direction, &s_to_r);
    f64 c = tuple_dot(&s_to_r, &s_to_r) - 1.0;

    f64 discriminant = pow(b, 2) - 4.0 * a * c;

    if (discriminant < 0) {
        goto out;
    }

    f64 t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    f64 t2 = (-b + sqrt(discriminant)) / (2.0 * a);

    intersects_add(&inters, min(t1, t2), s);
    intersects_add(&inters, max(t1, t2), s);

out:
    return inters;
}

Intersects intersect_world(const Ray *r, const World *w)
{
    Intersects xs;
    intersects_init(&xs);

    /* TODO(Linus): Optimize? */
    for (size_t i = 0; i < w->objects.len; ++i) {
        Object *o = w->objects.objects + i;
        Intersects sxs = intersect_sphere(o, r);
        intersects_merge(&xs, &sxs);
        intersects_destroy(&sxs);
    }

    return xs;
}
