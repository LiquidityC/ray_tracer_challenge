#include <stdio.h>
#include <stdlib.h>
#include "intersection.h"

void intersects_init(Intersects *xs)
{
    xs->len = 0;
    xs->head = NULL;
}

void intersects_add(Intersects *xs, f32 t, f32 object)
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
        printf("%.1f %.1f\n", ptr->x.t, ptr->x.object);
        free(ptr);
        ptr = next;
    }
    xs->head = NULL;
}

Intersects intersect_sphere(Sphere *s, Ray *r)
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
    f32 a = tuple_dot(&tr.direction, &tr.direction);
    f32 b = 2.0 * tuple_dot(&tr.direction, &s_to_r);
    f32 c = tuple_dot(&s_to_r, &s_to_r) - 1.0;

    f32 discriminant = pow(b, 2) - 4.0 * a * c;

    if (discriminant < 0) {
        goto out;
    }

    f32 t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    f32 t2 = (-b + sqrt(discriminant)) / (2.0 * a);

    intersects_add(&inters, min(t1, t2), s->id);
    intersects_add(&inters, max(t1, t2), s->id);

out:
    return inters;
}
