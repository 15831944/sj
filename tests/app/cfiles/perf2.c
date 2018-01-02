#include <lib/common/common.h>
#ifdef WIN32
#define GLEW_STATIC
#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif
/**
* Maximum number of attributes per vertex
*
* @private
*/
#define MAX_VERTEX_ATTRIBUTE 16    
#ifdef EMSCRIPTEN
#include <GLES3/gl3.h>
#endif
#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif
#ifdef EMSCRIPTEN
#include <SDL.h>
#endif
#ifdef WIN32
#include <SDL2/SDL.h>
#endif
#ifdef __APPLE__
#include <SDL2/SDL.h>
#endif
#include <assert.h>
#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif
#ifdef EMSCRIPTEN
#include <emscripten/html5.h>
#endif
#include <float.h>
#include <ft2build.h>
#include <gl/glu.h>
#include <lib/ui/obj_parser.h>
#include <limits.h>
#include <math.h>
#include <png.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include FT_FREETYPE_H
#include FT_LCD_FILTER_H
#include FT_STROKER_H

typedef struct vector_td vector_t;
typedef struct vertex_attribute_td vertex_attribute_t;
typedef struct vertex_buffer_td vertex_buffer_t;
const char* sjg_string1 = "shaders/v3f-t2f.vert";
const char* sjg_string10 = "shaders/v3f-t2f-n3f-phong.vert";
const char* sjg_string11 = "shaders/v3f-t2f-n3f-phong.frag";
const char* sjg_string12 = "shaders/v3f-t2f-c4f.vert";
const char* sjg_string13 = "shaders/v3f-t2f-c4f.frag";
const char* sjg_string14 = "vertex:3f,tex_coord:2f,normal:3f";
const char* sjg_string15 = "shaders/saturate.frag";
const char* sjg_string16 = "FPS: ";
const char* sjg_string17 = "viewport being pop'ed is wrong";
const char* sjg_string2 = "shaders/blur-horizontal.frag";
const char* sjg_string3 = "shaders/blur-vertical.frag";
const char* sjg_string4 = "shaders/fade.frag";
const char* sjg_string5 = "shaders/v3f-c4f.vert";
const char* sjg_string6 = "shaders/v3f-c4f.frag";
const char* sjg_string7 = "shaders/v3f-t2f.frag";
const char* sjg_string8 = "shaders/v3f-n3f-phong.vert";
const char* sjg_string9 = "shaders/v3f-n3f-phong.frag";

typedef struct {
    float x, y, z;    // position
    float r, g, b, a; // color
} vertex3_color4_t; 
typedef struct {
    float x, y, z;    // position
    float s, t;       // texture
} vertex3_texture2_t;   
typedef struct {
    float x, y, z;    // position
    float s, t;       // texture
    float r, g, b, a; // color
} vertex3_texture2_color3_t;    
/**
* Tuple of 4 ints.
*
* Each field can be addressed using several aliases:
*  - First component:  <b>x</b>, <b>r</b>, <b>red</b> or <b>vstart</b>
*  - Second component: <b>y</b>, <b>g</b>, <b>green</b> or <b>vcount</b>
*  - Third component:  <b>z</b>, <b>b</b>, <b>blue</b>, <b>width</b> or <b>istart</b>
*  - Fourth component: <b>w</b>, <b>a</b>, <b>alpha</b>, <b>height</b> or <b>icount</b>
*
*/
typedef union
{
    int data[4];    /**< All compoments at once     */
    struct {
        int x;      /**< Alias for first component  */
        int y;      /**< Alias for second component */
        int z;      /**< Alias for third component  */
        int w;      /**< Alias for fourht component */
    };
    struct {
        int x_;     /**< Alias for first component  */
        int y_;     /**< Alias for second component */
        int width;  /**< Alias for third component  */
        int height; /**< Alias for fourth component */
    };
    struct {
        int r;      /**< Alias for first component  */
        int g;      /**< Alias for second component */
        int b;      /**< Alias for third component  */
        int a;      /**< Alias for fourth component */
    };
    struct {
        int red;    /**< Alias for first component  */
        int green;  /**< Alias for second component */
        int blue;   /**< Alias for third component  */
        int alpha;  /**< Alias for fourth component */
    };
    struct {
        int vstart; /**< Alias for first component  */
        int vcount; /**< Alias for second component */
        int istart; /**< Alias for third component  */
        int icount; /**< Alias for fourth component */
    };
} ivec4;
/**
* Tuple of 3 ints.
*
* Each field can be addressed using several aliases:
*  - First component:  <b>x</b>, <b>r</b> or <b>red</b>
*  - Second component: <b>y</b>, <b>g</b> or <b>green</b>
*  - Third component:  <b>z</b>, <b>b</b> or <b>blue</b>
*
*/
typedef union
{
    int data[3];    /**< All compoments at once     */
    struct {
        int x;      /**< Alias for first component  */
        int y;      /**< Alias for second component */
        int z;      /**< Alias for third component  */
    };
    struct {
        int r;      /**< Alias for first component  */
        int g;      /**< Alias for second component */
        int b;      /**< Alias for third component  */
    };
    struct {
        int red;    /**< Alias for first component  */
        int green;  /**< Alias for second component */
        int blue;   /**< Alias for third component  */
    };
} ivec3;
/**
* Tuple of 2 ints.
*
* Each field can be addressed using several aliases:
*  - First component: <b>x</b>, <b>s</b> or <b>start</b>
*  - Second component: <b>y</b>, <b>t</b> or <b>end</b>
*
*/
typedef union
{
    int data[2];    /**< All compoments at once     */
    struct {
        int x;      /**< Alias for first component  */
        int y;      /**< Alias for second component */
    };
    struct {
        int s;      /**< Alias for first component  */
        int t;      /**< Alias for second component */
    };
    struct {
        int start;  /**< Alias for first component  */
        int end;    /**< Alias for second component */
    };
} ivec2;
/**
* Tuple of 4 floats.
*
* Each field can be addressed using several aliases:
*  - First component:  <b>x</b>, <b>left</b>, <b>r</b> or <b>red</b>
*  - Second component: <b>y</b>, <b>top</b>, <b>g</b> or <b>green</b>
*  - Third component:  <b>z</b>, <b>width</b>, <b>b</b> or <b>blue</b>
*  - Fourth component: <b>w</b>, <b>height</b>, <b>a</b> or <b>alpha</b>
*/
typedef union
{
    float data[4];    /**< All compoments at once    */
    struct {
        float x;      /**< Alias for first component */
        float y;      /**< Alias for second component */
        float z;      /**< Alias for third component  */
        float w;      /**< Alias for fourth component */
    };
    struct {
        float left;   /**< Alias for first component */
        float top;    /**< Alias for second component */
        float width;  /**< Alias for third component  */
        float height; /**< Alias for fourth component */
    };
    struct {
        float r;      /**< Alias for first component */
        float g;      /**< Alias for second component */
        float b;      /**< Alias for third component  */
        float a;      /**< Alias for fourth component */
    };
    struct {
        float red;    /**< Alias for first component */
        float green;  /**< Alias for second component */
        float blue;   /**< Alias for third component  */
        float alpha;  /**< Alias for fourth component */
    };
} vec4;
/**
* Tuple of 3 floats
*
* Each field can be addressed using several aliases:
*  - First component:  <b>x</b>, <b>r</b> or <b>red</b>
*  - Second component: <b>y</b>, <b>g</b> or <b>green</b>
*  - Third component:  <b>z</b>, <b>b</b> or <b>blue</b>
*/
typedef union
{
    float data[3];   /**< All compoments at once    */
    struct {
        float x;     /**< Alias for first component */
        float y;     /**< Alias fo second component */
        float z;     /**< Alias fo third component  */
    };
    struct {
        float r;     /**< Alias for first component */
        float g;     /**< Alias fo second component */
        float b;     /**< Alias fo third component  */
    };
    struct {
        float red;   /**< Alias for first component */
        float green; /**< Alias fo second component */
        float blue;  /**< Alias fo third component  */
    };
} vec3;
/**
* Tuple of 2 floats
*
* Each field can be addressed using several aliases:
*  - First component:  <b>x</b> or <b>s</b>
*  - Second component: <b>y</b> or <b>t</b>
*/
typedef union
{
    float data[2]; /**< All components at once     */
    struct {
        float x;   /**< Alias for first component  */
        float y;   /**< Alias for second component */
    };
    struct {
        float s;   /**< Alias for first component  */
        float t;   /**< Alias for second component */
    };
} vec2;
/**
* A texture atlas is used to pack several small regions into a single texture.
*/
typedef struct texture_atlas_t
{
    /**
    * Allocated nodes
    */
    vector_t * nodes;
    /**
    *  Width (in pixels) of the underlying texture
    */
    size_t width;
    /**
    * Height (in pixels) of the underlying texture
    */
    size_t height;
    /**
    * Depth (in bytes) of the underlying texture
    */
    size_t depth;
    /**
    * Allocated surface size
    */
    size_t used;
    /**
    * Texture identity (OpenGL)
    */
    unsigned int id;
    /**
    * Atlas data
    */
    unsigned char * data;
} texture_atlas_t;    
#undef __FTERRORS_H__
#define FT_ERRORDEF( e, v, s )  { e, s },
#define FT_ERROR_START_LIST     {
#define FT_ERROR_END_LIST       { 0, 0 } };
const struct {
    int          code;
    const char*  message;
} FT_Errors[] =
#include FT_ERRORS_H    
/**
* A list of possible ways to render a glyph.
*/
typedef enum rendermode_t
{
    RENDER_NORMAL,
    RENDER_OUTLINE_EDGE,
    RENDER_OUTLINE_POSITIVE,
    RENDER_OUTLINE_NEGATIVE,
    RENDER_SIGNED_DISTANCE_FIELD
} rendermode_t;
/**
* A structure that hold a kerning value relatively to a Unicode
* codepoint.
*
* This structure cannot be used alone since the (necessary) right
* Unicode codepoint is implicitely held by the owner of this structure.
*/
typedef struct kerning_t
{
    /**
    * Left Unicode codepoint in the kern pair in UTF-32 LE encoding.
    */
    uint32_t codepoint;
    /**
    * Kerning value (in fractional pixels).
    */
    float kerning;
} kerning_t;
/*
* Glyph metrics:
* --------------
*
*                       xmin                     xmax
*                        |                         |
*                        |<-------- width -------->|
*                        |                         |
*              |         +-------------------------+----------------- ymax
*              |         |    ggggggggg   ggggg    |     ^        ^
*              |         |   g:::::::::ggg::::g    |     |        |
*              |         |  g:::::::::::::::::g    |     |        |
*              |         | g::::::ggggg::::::gg    |     |        |
*              |         | g:::::g     g:::::g     |     |        |
*    offset_x -|-------->| g:::::g     g:::::g     |  offset_y    |
*              |         | g:::::g     g:::::g     |     |        |
*              |         | g::::::g    g:::::g     |     |        |
*              |         | g:::::::ggggg:::::g     |     |        |
*              |         |  g::::::::::::::::g     |     |      height
*              |         |   gg::::::::::::::g     |     |        |
*  baseline ---*---------|---- gggggggg::::::g-----*--------      |
*            / |         |             g:::::g     |              |
*     origin   |         | gggggg      g:::::g     |              |
*              |         | g:::::gg   gg:::::g     |              |
*              |         |  g::::::ggg:::::::g     |              |
*              |         |   gg:::::::::::::g      |              |
*              |         |     ggg::::::ggg        |              |
*              |         |         gggggg          |              v
*              |         +-------------------------+----------------- ymin
*              |                                   |
*              |------------- advance_x ---------->|
*/
/**
* A structure that describe a glyph.
*/
typedef struct texture_glyph_t
{
    /**
    * Unicode codepoint this glyph represents in UTF-32 LE encoding.
    */
    uint32_t codepoint;
    /**
    * Glyph's width in pixels.
    */
    size_t width;
    /**
    * Glyph's height in pixels.
    */
    size_t height;
    /**
    * Glyph's left bearing expressed in integer pixels.
    */
    int offset_x;
    /**
    * Glyphs's top bearing expressed in integer pixels.
    *
    * Remember that this is the distance from the baseline to the top-most
    * glyph scanline, upwards y coordinates being positive.
    */
    int offset_y;
    /**
    * For horizontal text layouts, this is the horizontal distance (in
    * fractional pixels) used to increment the pen position when the glyph is
    * drawn as part of a string of text.
    */
    float advance_x;
    /**
    * For vertical text layouts, this is the vertical distance (in fractional
    * pixels) used to increment the pen position when the glyph is drawn as
    * part of a string of text.
    */
    float advance_y;
    /**
    * First normalized texture coordinate (x) of top-left corner
    */
    float s0;
    /**
    * Second normalized texture coordinate (y) of top-left corner
    */
    float t0;
    /**
    * First normalized texture coordinate (x) of bottom-right corner
    */
    float s1;
    /**
    * Second normalized texture coordinate (y) of bottom-right corner
    */
    float t1;
    /**
    * A vector of kerning pairs relative to this glyph.
    */
    vector_t * kerning;
    /**
    * Mode this glyph was rendered
    */
    rendermode_t rendermode;
    /**
    * Glyph outline thickness
    */
    float outline_thickness;
} texture_glyph_t;
typedef struct texture_atlas_t texture_atlas_td; 
/**
*  Texture font structure.
*/
typedef struct texture_font_t
{
    /**
    * Vector of glyphs contained in this font.
    */
    vector_t * glyphs;
    /**
    * Atlas structure to store glyphs data.
    */
    texture_atlas_td * atlas;
    /**
    * font location
    */
    enum {
        TEXTURE_FONT_FILE = 0,
        TEXTURE_FONT_MEMORY,
    } location;
    union {
        /**
        * Font filename, for when location == TEXTURE_FONT_FILE
        */
        char *filename;
        /**
        * Font memory address, for when location == TEXTURE_FONT_MEMORY
        */
        struct {
            const void *base;
            size_t size;
        } memory;
    };
    /**
    * Font size
    */
    float size;
    /**
    * Whether to use autohint when rendering font
    */
    int hinting;
    /**
    * Mode the font is rendering its next glyph
    */
    rendermode_t rendermode;
    /**
    * Outline thickness
    */
    float outline_thickness;
    /**
    * Whether to use our own lcd filter.
    */
    int filtering;
    /**
    * LCD filter weights
    */
    unsigned char lcd_weights[5];
    /**
    * Whether to use kerning if available
    */
    int kerning;
    /**
    * This field is simply used to compute a default line spacing (i.e., the
    * baseline-to-baseline distance) when writing text with this font. Note
    * that it usually is larger than the sum of the ascender and descender
    * taken as absolute values. There is also no guarantee that no glyphs
    * extend above or below subsequent baselines when using this distance.
    */
    float height;
    /**
    * This field is the distance that must be placed between two lines of
    * text. The baseline-to-baseline distance should be computed as:
    * ascender - descender + linegap
    */
    float linegap;
    /**
    * The ascender is the vertical distance from the horizontal baseline to
    * the highest 'character' coordinate in a font face. Unfortunately, font
    * formats define the ascender differently. For some, it represents the
    * ascent of all capital latin characters (without accents), for others it
    * is the ascent of the highest accented character, and finally, other
    * formats define it as being equal to bbox.yMax.
    */
    float ascender;
    /**
    * The descender is the vertical distance from the horizontal baseline to
    * the lowest 'character' coordinate in a font face. Unfortunately, font
    * formats define the descender differently. For some, it represents the
    * descent of all capital latin characters (without accents), for others it
    * is the ascent of the lowest accented character, and finally, other
    * formats define it as being equal to bbox.yMin. This field is negative
    * for values below the baseline.
    */
    float descender;
    /**
    * The position of the underline line for this face. It is the center of
    * the underlining stem. Only relevant for scalable formats.
    */
    float underline_position;
    /**
    * The thickness of the underline for this face. Only relevant for scalable
    * formats.
    */
    float underline_thickness;
} texture_font_t;
/**
*  Generic vector structure.
*
* @memberof vector
*/
struct vector_td
{
    /** Pointer to dynamically allocated items. */
    void * items;
    /** Number of items that can be held in currently allocated storage. */
    size_t capacity;
    /** Number of items. */
    size_t size;
    /** Size (in bytes) of a single item. */
    size_t item_size;
};
/**
*  Generic vertex attribute.
*/
struct vertex_attribute_td
{
    /**
    *  atribute name
    */
    GLchar * name;
    /**
    * index of the generic vertex attribute to be modified.
    */
    GLuint index;
    /**
    * Number of components per generic vertex attribute.
    *
    * Must be 1, 2, 3, or 4. The initial value is 4.
    */
    GLint size;
    /**
    *  data type of each component in the array.
    *
    *  Symbolic constants GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT,
    *  GL_UNSIGNED_SHORT, GL_INT, GL_UNSIGNED_INT, GL_FLOAT, or GL_DOUBLE are
    *  accepted. The initial value is GL_FLOAT.
    */
    GLenum type;
    /**
    *  whether fixed-point data values should be normalized (GL_TRUE) or
    *  converted directly as fixed-point values (GL_FALSE) when they are
    *  accessed.
    */
    GLboolean normalized;
    /**
    *  byte offset between consecutive generic vertex attributes.
    *
    *  If stride is 0, the generic vertex attributes are understood to be
    *  tightly packed in the array. The initial value is 0.
    */
    GLsizei stride;
    /**
    *  pointer to the first component of the first attribute element in the
    *  array.
    */
    GLvoid * pointer;
    /**
    * pointer to the function that enable this attribute.
    */
    void ( * enable )(void *);
};
/**
* Generic vertex buffer.
*/
struct vertex_buffer_td
{
    /** Format of the vertex buffer. */
    char * format;
    /** Vector of vertices. */
    vector_t * vertices;
    #ifdef FREETYPE_GL_USE_VAO
    /** GL identity of the Vertex Array Object */
    GLuint VAO_id;
    #endif
    /** GL identity of the vertices buffer. */
    GLuint vertices_id;
    /** Vector of indices. */
    vector_t * indices;
    /** GL identity of the indices buffer. */
    GLuint indices_id;
    /** Current size of the vertices buffer in GPU */
    size_t GPU_vsize;
    /** Current size of the indices buffer in GPU*/
    size_t GPU_isize;
    /** GL primitives to render. */
    GLenum mode;
    /** Whether the vertex buffer needs to be uploaded to GPU memory. */
    char state;
    /** Individual items */
    vector_t * items;
    /** Array of attributes. */
    vertex_attribute_t *attributes[MAX_VERTEX_ATTRIBUTE];
};
#define sjs_hash_type_bool_typeId 36
#define sjs_log_typeId 41
#define sjs_windowrenderer_typeId 42
#define sjs_color_typeId 44
#define sjs_size_typeId 48
#define sjs_mat4_typeId 49
#define sjs_rect_typeId 50
#define sjs_scene2d_typeId 47
#define sjs_array_char_typeId 60
#define sjs_string_typeId 51
#define sjs_vec3_typeId 53
#define sjs_light_typeId 52
#define sji_model_typeId 54
#define sjs_array_heap_iface_model_typeId 158
#define sjs_list_heap_iface_model_typeId 55
#define sjs_point_typeId 157
#define sjs_mouseevent_typeId 56
#define sjs_hash_string_weak_iface_model_typeId 57
#define sji_element_typeId 64
#define sjs_hash_string_weak_iface_element_typeId 65
#define sjs_array_heap_iface_animation_typeId 71
#define sjs_list_heap_iface_animation_typeId 70
#define sjs_animator_typeId 68
#define sji_animation_typeId 69
#define sjs_shader_typeId 72
#define sjs_fontkey_typeId 73
#define sjs_font_typeId 74
#define sjs_hash_fontkey_weak_font_typeId 75
#define sjs_array_rect_typeId 82
#define sjs_list_rect_typeId 81
#define sjs_array_u32_typeId 84
#define sjs_list_u32_typeId 83
#define sjs_style_typeId 85
#define sjs_vec4_typeId 86
#define sjs_array_bool_typeId 87
#define sjs_array_f32_typeId 92
#define sjs_test_typeId 91

typedef struct td_sjs_hash_type_bool sjs_hash_type_bool;
typedef struct td_sjs_log sjs_log;
typedef struct td_sjs_windowrenderer sjs_windowrenderer;
typedef struct td_sjs_color sjs_color;
typedef struct td_sjs_size sjs_size;
typedef struct td_sjs_mat4 sjs_mat4;
typedef struct td_sjs_rect sjs_rect;
typedef struct td_sjs_scene2d sjs_scene2d;
typedef struct td_sjs_array_char sjs_array_char;
typedef struct td_sjs_string sjs_string;
typedef struct td_sjs_vec3 sjs_vec3;
typedef struct td_sjs_light sjs_light;
typedef struct td_sji_model sji_model;
typedef struct td_sjs_array_heap_iface_model sjs_array_heap_iface_model;
typedef struct td_sjs_list_heap_iface_model sjs_list_heap_iface_model;
typedef struct td_sjs_point sjs_point;
typedef struct td_sjs_mouseevent sjs_mouseevent;
typedef struct td_sji_model_vtbl sji_model_vtbl;
typedef struct td_sjs_hash_string_weak_iface_model sjs_hash_string_weak_iface_model;
typedef struct td_sji_element_vtbl sji_element_vtbl;
typedef struct td_sji_element sji_element;
typedef struct td_sjs_hash_string_weak_iface_element sjs_hash_string_weak_iface_element;
typedef struct td_sjs_array_heap_iface_animation sjs_array_heap_iface_animation;
typedef struct td_sjs_list_heap_iface_animation sjs_list_heap_iface_animation;
typedef struct td_sjs_animator sjs_animator;
typedef struct td_sji_animation_vtbl sji_animation_vtbl;
typedef struct td_sji_animation sji_animation;
typedef struct td_sjs_shader sjs_shader;
typedef struct td_sjs_fontkey sjs_fontkey;
typedef struct td_sjs_font sjs_font;
typedef struct td_sjs_hash_fontkey_weak_font sjs_hash_fontkey_weak_font;
typedef struct td_sjs_array_rect sjs_array_rect;
typedef struct td_sjs_list_rect sjs_list_rect;
typedef struct td_sjs_array_u32 sjs_array_u32;
typedef struct td_sjs_list_u32 sjs_list_u32;
typedef struct td_sjs_style sjs_style;
typedef struct td_sjs_vec4 sjs_vec4;
typedef struct td_sjs_array_bool sjs_array_bool;
typedef struct td_sjs_array_f32 sjs_array_f32;
typedef struct td_sjs_test sjs_test;

struct td_sjs_hash_type_bool {
    int _refCount;
    void* _hash;
};

struct td_sjs_log {
    int _refCount;
    int32_t minlevel;
    sjs_hash_type_bool traceincludes;
    sjs_hash_type_bool debugincludes;
    sjs_hash_type_bool infoincludes;
    sjs_hash_type_bool warnincludes;
    sjs_hash_type_bool errorincludes;
    sjs_hash_type_bool fatalincludes;
};

struct td_sjs_windowrenderer {
    int _refCount;
    SDL_Window* win;
    SDL_Renderer* ren;
};

struct td_sjs_color {
    int _refCount;
    float r;
    float g;
    float b;
    float a;
};

struct td_sjs_size {
    int _refCount;
    int32_t w;
    int32_t h;
};

struct td_sjs_mat4 {
    int _refCount;
    float m00;
    float m01;
    float m02;
    float m03;
    float m10;
    float m11;
    float m12;
    float m13;
    float m20;
    float m21;
    float m22;
    float m23;
    float m30;
    float m31;
    float m32;
    float m33;
};

struct td_sjs_rect {
    int _refCount;
    int32_t x;
    int32_t y;
    int32_t w;
    int32_t h;
};

struct td_sjs_scene2d {
    int _refCount;
    sjs_size _size;
    sjs_mat4 model;
    sjs_mat4 view;
    sjs_mat4 projection;
    sjs_rect windowrect;
};

struct td_sjs_array_char {
    int _refCount;
    int32_t datasize;
    void* data;
    bool isglobal;
    int32_t count;
};

struct td_sjs_string {
    int _refCount;
    int32_t count;
    sjs_array_char data;
    bool _isnullterminated;
};

struct td_sjs_vec3 {
    int _refCount;
    float x;
    float y;
    float z;
};

struct td_sjs_light {
    int _refCount;
    sjs_vec3 pos;
    sjs_color diffusecolor;
    sjs_color speccolor;
};

struct td_sji_model {
    sjs_object* _parent;
    sji_model_vtbl* _vtbl;
};

struct td_sjs_array_heap_iface_model {
    int _refCount;
    int32_t datasize;
    void* data;
    bool isglobal;
    int32_t count;
};

struct td_sjs_list_heap_iface_model {
    int _refCount;
    sjs_array_heap_iface_model array;
};

struct td_sjs_point {
    int _refCount;
    int32_t x;
    int32_t y;
};

struct td_sjs_mouseevent {
    int _refCount;
    int32_t eventtype;
    sjs_point point;
    bool iscaptured;
    bool isleftdown;
};

struct td_sji_model_vtbl {
    void (*destroy)(void* _this);
    void (*asinterface)(sjs_object* _this, int typeId, sjs_interface* _return);
    void (*getclasstype)(sjs_object* _parent, int32_t* _return);
    void (*update)(sjs_object* _parent, sjs_rect* scenerect, sjs_mat4* projection, sjs_mat4* view, sjs_mat4* world, sjs_light* light);
    void (*getz)(sjs_object* _parent, float* _return);
    void (*getcenter)(sjs_object* _parent, sjs_vec3* _return);
    void (*getcenter_heap)(sjs_object* _parent, sjs_vec3** _return);
    void (*getworld)(sjs_object* _parent, sjs_mat4* _return);
    void (*getworld_heap)(sjs_object* _parent, sjs_mat4** _return);
    void (*renderorqueue)(sjs_object* _parent, sjs_list_heap_iface_model* zqueue);
    void (*render)(sjs_object* _parent);
    void (*firemouseevent)(sjs_object* _parent, sjs_mouseevent* mouseevent);
};

struct td_sjs_hash_string_weak_iface_model {
    int _refCount;
    void* _hash;
};

struct td_sji_element_vtbl {
    void (*destroy)(void* _this);
    void (*asinterface)(sjs_object* _this, int typeId, sjs_interface* _return);
    void (*getclasstype)(sjs_object* _parent, int32_t* _return);
    void (*getsize)(sjs_object* _parent, sjs_size* maxsize, sjs_size* _return);
    void (*getsize_heap)(sjs_object* _parent, sjs_size* maxsize, sjs_size** _return);
    void (*getrect)(sjs_object* _parent, sjs_rect* _return);
    void (*getrect_heap)(sjs_object* _parent, sjs_rect** _return);
    void (*setrect)(sjs_object* _parent, sjs_rect* rect);
    void (*render)(sjs_object* _parent, sjs_scene2d* scene);
    void (*firemouseevent)(sjs_object* _parent, sjs_mouseevent* mouseevent, bool* _return);
};

struct td_sji_element {
    sjs_object* _parent;
    sji_element_vtbl* _vtbl;
};

struct td_sjs_hash_string_weak_iface_element {
    int _refCount;
    void* _hash;
};

struct td_sjs_array_heap_iface_animation {
    int _refCount;
    int32_t datasize;
    void* data;
    bool isglobal;
    int32_t count;
};

struct td_sjs_list_heap_iface_animation {
    int _refCount;
    sjs_array_heap_iface_animation array;
};

struct td_sjs_animator {
    int _refCount;
    sjs_list_heap_iface_animation animations;
    int32_t current;
};

struct td_sji_animation_vtbl {
    void (*destroy)(void* _this);
    void (*asinterface)(sjs_object* _this, int typeId, sjs_interface* _return);
    void (*getclasstype)(sjs_object* _parent, int32_t* _return);
    void (*nextframe)(sjs_object* _parent, int32_t time, bool* _return);
};

struct td_sji_animation {
    sjs_object* _parent;
    sji_animation_vtbl* _vtbl;
};

struct td_sjs_shader {
    int _refCount;
    sjs_string vertex;
    sjs_string pixel;
    GLuint id;
};

struct td_sjs_fontkey {
    int _refCount;
    sjs_string src;
    float size;
};

struct td_sjs_font {
    int _refCount;
    sjs_string src;
    float size;
    texture_font_t* font;
    texture_atlas_t* atlas;
};

struct td_sjs_hash_fontkey_weak_font {
    int _refCount;
    void* _hash;
};

struct td_sjs_array_rect {
    int _refCount;
    int32_t datasize;
    void* data;
    bool isglobal;
    int32_t count;
};

struct td_sjs_list_rect {
    int _refCount;
    sjs_array_rect array;
};

struct td_sjs_array_u32 {
    int _refCount;
    int32_t datasize;
    void* data;
    bool isglobal;
    int32_t count;
};

struct td_sjs_list_u32 {
    int _refCount;
    sjs_array_u32 array;
};

struct td_sjs_style {
    int _refCount;
};

struct td_sjs_vec4 {
    int _refCount;
    float x;
    float y;
    float z;
    float w;
};

struct td_sjs_array_bool {
    int _refCount;
    int32_t datasize;
    void* data;
    bool isglobal;
    int32_t count;
};

struct td_sjs_array_f32 {
    int _refCount;
    int32_t datasize;
    void* data;
    bool isglobal;
    int32_t count;
};

struct td_sjs_test {
    int _refCount;
    int32_t funcid;
    int32_t lastfuncid;
    sjs_array_f32 datax;
    sjs_array_f32 datay;
    float rotatex;
    float rotatey;
    float rotatez;
    sjs_array_f32 datavert1x;
    sjs_array_f32 datavert1y;
    sjs_array_f32 datavert2x;
    sjs_array_f32 datavert2y;
    sjs_array_f32 datavert3x;
    sjs_array_f32 datavert3y;
    sjs_array_f32 datavert4x;
    sjs_array_f32 datavert4y;
    sjs_array_f32 datavert5x;
    sjs_array_f32 datavert5y;
    sjs_array_f32 datahotizont1x;
    sjs_array_f32 datahotizont1y;
    sjs_array_f32 datahotizont2x;
    sjs_array_f32 datahotizont2y;
    sjs_array_f32 datahotizont3x;
    sjs_array_f32 datahotizont3y;
    sjs_array_f32 datahotizont4x;
    sjs_array_f32 datahotizont4y;
    sjs_array_f32 datahotizont5x;
    sjs_array_f32 datahotizont5y;
    sjs_rect _rect;
};

sji_element_vtbl sjs_test_element_vtbl;
#ifndef type_bool_hash_typedef
#define type_bool_hash_typedef
KHASH_INIT_TYPEDEF(type_bool_hash_type, int32_t, bool)
#endif
#ifndef type_bool_hash_typedef
#define type_bool_hash_typedef
KHASH_INIT_TYPEDEF(type_bool_hash_type, int32_t, bool)
#endif
#ifndef string_weak_iface_model_hash_typedef
#define string_weak_iface_model_hash_typedef
KHASH_INIT_TYPEDEF(string_weak_iface_model_hash_type, sjs_string, sji_model)
#endif
#ifndef string_weak_iface_model_hash_typedef
#define string_weak_iface_model_hash_typedef
KHASH_INIT_TYPEDEF(string_weak_iface_model_hash_type, sjs_string, sji_model)
#endif
#ifndef string_weak_iface_element_hash_typedef
#define string_weak_iface_element_hash_typedef
KHASH_INIT_TYPEDEF(string_weak_iface_element_hash_type, sjs_string, sji_element)
#endif
#ifndef string_weak_iface_element_hash_typedef
#define string_weak_iface_element_hash_typedef
KHASH_INIT_TYPEDEF(string_weak_iface_element_hash_type, sjs_string, sji_element)
#endif
double *
make_distance_mapd( double *img,
unsigned int width, unsigned int height );
unsigned char *
make_distance_mapb( unsigned char *img,
unsigned int width, unsigned int height );    
/*
* Compute the local gradient at edge pixels using convolution filters.
* The gradient is computed only at edge pixels. At other places in the
* image, it is never used, and it's mostly zero anyway.
*/
void computegradient(double *img, int w, int h, double *gx, double *gy);
/*
* A somewhat tricky function to approximate the distance to an edge in a
* certain pixel, with consideration to either the local gradient (gx,gy)
* or the direction to the pixel (dx,dy) and the pixel greyscale value a.
* The latter alternative, using (dx,dy), is the metric used by edtaa2().
* Using a local estimate of the edge gradient (gx,gy) yields much better
* accuracy at and near edges, and reduces the error even at distant pixels
* provided that the gradient direction is accurately estimated.
*/
double edgedf(double gx, double gy, double a);
double distaa3(double *img, double *gximg, double *gyimg, int w, int c, int xc, int yc, int xi, int yi);
// Shorthand macro: add ubiquitous parameters dist, gx, gy, img and w and call distaa3()
#define DISTAA(c,xc,yc,xi,yi) (distaa3(img, gx, gy, w, c, xc, yc, xi, yi))
void edtaa3(double *img, double *gx, double *gy, int w, int h, short *distx, short *disty, double *dist);  
#ifndef fontkey_weak_font_hash_typedef
#define fontkey_weak_font_hash_typedef
KHASH_INIT_TYPEDEF(fontkey_weak_font_hash_type, sjs_fontkey, sjs_font*)
#endif
#ifndef fontkey_weak_font_hash_typedef
#define fontkey_weak_font_hash_typedef
KHASH_INIT_TYPEDEF(fontkey_weak_font_hash_type, sjs_fontkey, sjs_font*)
#endif
void glid_retain(GLuint id);
bool glid_release(GLuint id);
void glid_gethash(GLuint id, uint32_t* result);
void glid_isequal(GLuint id1, GLuint id2, bool* result);
/* Freetype GL - A C OpenGL Freetype engine
*
* Distributed under the OSI-approved BSD 2-Clause License.  See accompanying
* file `LICENSE` for more details.
*/
/**
* Read a fragment or vertex shader from a file
*
* @param filename file to read shader from
* @return         a newly-allocated text buffer containing code. This buffer
*                 must be freed after usage.
*
*/
char *
shader_read( const char *filename );
/**
* Compile a shader from a text buffer.
*
* @param source code of the shader
* @param type   type of the shader
*
* @return a handle on the compiled program
*
*/
GLuint
shader_compile( const char* source,
const GLenum type );
/**
* Load a vertex and fragment shader sources and build program
*
* @param  vert_filename vertex shader filename
* @param  frag_filename fragment shader filename
*
* @return a handle on the built program
*
*/
GLuint
shader_load( const char * vert_filename,
const char * frag_filename );    
void add_text(vertex_buffer_t * buffer, texture_font_t * font, char *text, int textlen, vec4 * color, vec2 * pen);   
vec2 get_text_size(texture_font_t * font, char *text);
/**
* Creates a new empty texture atlas.
*
* @param   width   width of the atlas
* @param   height  height of the atlas
* @param   depth   bit depth of the atlas
* @return          a new empty texture atlas.
*
*/
texture_atlas_t *
texture_atlas_new( const size_t width,
const size_t height,
const size_t depth );
/**
*  Deletes a texture atlas.
*
*  @param self a texture atlas structure
*
*/
void
texture_atlas_delete( texture_atlas_t * self );
/**
*  Allocate a new region in the atlas.
*
*  @param self   a texture atlas structure
*  @param width  width of the region to allocate
*  @param height height of the region to allocate
*  @return       Coordinates of the allocated region
*
*/
ivec4
texture_atlas_get_region( texture_atlas_t * self,
const size_t width,
const size_t height );
/**
*  Upload data to the specified atlas region.
*
*  @param self   a texture atlas structure
*  @param x      x coordinate the region
*  @param y      y coordinate the region
*  @param width  width of the region
*  @param height height of the region
*  @param data   data to be uploaded into the specified region
*  @param stride stride of the data
*
*/
void
texture_atlas_set_region( texture_atlas_t * self,
const size_t x,
const size_t y,
const size_t width,
const size_t height,
const unsigned char *data,
const size_t stride );
/**
*  Remove all allocated regions from the atlas.
*
*  @param self   a texture atlas structure
*/
void
texture_atlas_clear( texture_atlas_t * self );    
/**
* This function creates a new texture font from given filename and size.  The
* texture atlas is used to store glyph on demand. Note the depth of the atlas
* will determine if the font is rendered as alpha channel only (depth = 1) or
* RGB (depth = 3) that correspond to subpixel rendering (if available on your
* freetype implementation).
*
* @param atlas     A texture atlas
* @param pt_size   Size of font to be created (in points)
* @param filename  A font filename
*
* @return A new empty font (no glyph inside yet)
*
*/
texture_font_t *
texture_font_new_from_file( texture_atlas_t * atlas,
const float pt_size,
const char * filename );
/**
* This function creates a new texture font from a memory location and size.
* The texture atlas is used to store glyph on demand. Note the depth of the
* atlas will determine if the font is rendered as alpha channel only
* (depth = 1) or RGB (depth = 3) that correspond to subpixel rendering (if
* available on your freetype implementation).
*
* @param atlas       A texture atlas
* @param pt_size     Size of font to be created (in points)
* @param memory_base Start of the font file in memory
* @param memory_size Size of the font file memory region, in bytes
*
* @return A new empty font (no glyph inside yet)
*
*/
texture_font_t *
texture_font_new_from_memory( texture_atlas_t *atlas,
float pt_size,
const void *memory_base,
size_t memory_size );
/**
* Delete a texture font. Note that this does not delete the glyph from the
* texture atlas.
*
* @param self a valid texture font
*/
void
texture_font_delete( texture_font_t * self );
/**
* Request a new glyph from the font. If it has not been created yet, it will
* be.
*
* @param self      A valid texture font
* @param codepoint Character codepoint to be loaded in UTF-8 encoding.
*
* @return A pointer on the new glyph or 0 if the texture atlas is not big
*         enough
*
*/
texture_glyph_t *
texture_font_get_glyph( texture_font_t * self,
const char * codepoint );
/** 
* Request an already loaded glyph from the font. 
* 
* @param self      A valid texture font
* @param codepoint Character codepoint to be found in UTF-8 encoding.
*
* @return A pointer on the glyph or 0 if the glyph is not loaded
*/
texture_glyph_t *
texture_font_find_glyph( texture_font_t * self,
const char * codepoint );
/**
* Request the loading of a given glyph.
*
* @param self       A valid texture font
* @param codepoints Character codepoint to be loaded in UTF-8 encoding.
*
* @return One if the glyph could be loaded, zero if not.
*/
int
texture_font_load_glyph( texture_font_t * self,
const char * codepoints );
/**
* Request the loading of several glyphs at once.
*
* @param self       A valid texture font
* @param codepoints Character codepoints to be loaded in UTF-8 encoding. May
*                   contain duplicates.
*
* @return Number of missed glyph if the texture is not big enough to hold
*         every glyphs.
*/
size_t
texture_font_load_glyphs( texture_font_t * self,
const char * codepoints );
/*
*Increases the size of a fonts texture atlas
*Invalidates all pointers to font->atlas->data
*Changes the UV Coordinates of existing glyphs in the font
*
*@param self A valid texture font
*@param width_new Width of the texture atlas after resizing (must be bigger or equal to current width)
*@param height_new Height of the texture atlas after resizing (must be bigger or equal to current height)
*/
void
texture_font_enlarge_atlas( texture_font_t * self, size_t width_new,
size_t height_new);
/**
* Get the kerning between two horizontal glyphs.
*
* @param self      A valid texture glyph
* @param codepoint Character codepoint of the peceding character in UTF-8 encoding.
*
* @return x kerning value
*/
float
texture_glyph_get_kerning( const texture_glyph_t * self,
const char * codepoint );
/**
* Creates a new empty glyph
*
* @return a new empty glyph (not valid)
*/
texture_glyph_t *
texture_glyph_new( void );    
/**
* Returns the size in bytes of a given UTF-8 encoded character surrogate
*
* @param character  An UTF-8 encoded character
*
* @return  The length of the surrogate in bytes.
*/
size_t
utf8_surrogate_len( const char* character );
/**
* Return the length of the given UTF-8 encoded and
* NULL terminated string.
*
* @param string  An UTF-8 encoded string
*
* @return  The length of the string in characters.
*/
size_t
utf8_strlen( const char* string );
/**
* Converts a given UTF-8 encoded character to its UTF-32 LE equivalent
*
* @param character  An UTF-8 encoded character
*
* @return  The equivalent of the given character in UTF-32 LE
*          encoding.
*/
uint32_t
utf8_to_utf32( const char * character );
/**
* @file   vector.h
* @author Nicolas Rougier (Nicolas.Rougier@inria.fr)
*
* @defgroup vector Vector
*
* The vector structure and accompanying functions loosely mimic the STL C++
* vector class. It is used by @ref texture-atlas (for storing nodes), @ref
* texture-font (for storing glyphs) and @ref font-manager (for storing fonts).
* More information at http://www.cppreference.com/wiki/container/vector/start
*/
/**
* Creates a new empty vector.
*
* @param   item_size    item size in bytes
* @return               a new empty vector
*
*/
vector_t *
vector_new( size_t item_size );
/**
*  Deletes a vector.
*
*  @param self a vector structure
*
*/
void
vector_delete( vector_t *self );
/**
*  Returns a pointer to the item located at specified index.
*
*  @param  self  a vector structure
*  @param  index the index of the item to be returned
*  @return       pointer on the specified item
*/
const void *
vector_get( const vector_t *self,
size_t index );
/**
*  Returns a pointer to the first item.
*
*  @param  self  a vector structure
*  @return       pointer on the first item
*/
const void *
vector_front( const vector_t *self );
/**
*  Returns a pointer to the last item
*
*  @param  self  a vector structure
*  @return pointer on the last item
*/
const void *
vector_back( const vector_t *self );
/**
*  Check if an item is contained within the vector.
*
*  @param  self  a vector structure
*  @param  item  item to be searched in the vector
*  @param  cmp   a pointer a comparison function
*  @return       1 if item is contained within the vector, 0 otherwise
*/
int
vector_contains( const vector_t *self,
const void *item,
int (*cmp)(const void *, const void *) );
/**
*  Checks whether the vector is empty.
*
*  @param  self  a vector structure
*  @return       1 if the vector is empty, 0 otherwise
*/
int
vector_empty( const vector_t *self );
/**
*  Returns the number of items
*
*  @param  self  a vector structure
*  @return       number of items
*/
size_t
vector_size( const vector_t *self );
/**
*  Reserve storage such that it can hold at last size items.
*
*  @param  self  a vector structure
*  @param  size  the new storage capacity
*/
void
vector_reserve( vector_t *self,
const size_t size );
/**
*  Returns current storage capacity
*
*  @param  self  a vector structure
*  @return       storage capacity
*/
size_t
vector_capacity( const vector_t *self );
/**
*  Decrease capacity to fit actual size.
*
*  @param  self  a vector structure
*/
void
vector_shrink( vector_t *self );
/**
*  Removes all items.
*
*  @param  self  a vector structure
*/
void
vector_clear( vector_t *self );
/**
*  Replace an item.
*
*  @param  self  a vector structure
*  @param  index the index of the item to be replaced
*  @param  item  the new item
*/
void
vector_set( vector_t *self,
const size_t index,
const void *item );
/**
*  Erase an item.
*
*  @param  self  a vector structure
*  @param  index the index of the item to be erased
*/
void
vector_erase( vector_t *self,
const size_t index );
/**
*  Erase a range of items.
*
*  @param  self  a vector structure
*  @param  first the index of the first item to be erased
*  @param  last  the index of the last item to be erased
*/
void
vector_erase_range( vector_t *self,
const size_t first,
const size_t last );
/**
*  Appends given item to the end of the vector.
*
*  @param  self a vector structure
*  @param  item the item to be inserted
*/
void
vector_push_back( vector_t *self,
const void *item );
/**
*  Removes the last item of the vector.
*
*  @param  self a vector structure
*/
void
vector_pop_back( vector_t *self );
/**
*  Resizes the vector to contain size items
*
*  If the current size is less than size, additional items are appended and
*  initialized with value. If the current size is greater than size, the
*  vector is reduced to its first size elements.
*
*  @param  self a vector structure
*  @param  size the new size
*/
void
vector_resize( vector_t *self,
const size_t size );
/**
*  Insert a single item at specified index.
*
*  @param  self  a vector structure
*  @param  index location before which to insert item
*  @param  item  the item to be inserted
*/
void
vector_insert( vector_t *self,
const size_t index,
const void *item );
/**
*  Insert raw data at specified index.
*
*  @param  self  a vector structure
*  @param  index location before which to insert item
*  @param  data  a pointer to the items to be inserted
*  @param  count the number of items to be inserted
*/
void
vector_insert_data( vector_t *self,
const size_t index,
const void * data,
const size_t count );
/**
*  Append raw data to the end of the vector.
*
*  @param  self  a vector structure
*  @param  data  a pointer to the items to be inserted
*  @param  count the number of items to be inserted
*/
void
vector_push_back_data( vector_t *self,
const void * data,
const size_t count );
/**
*  Sort vector items according to cmp function.
*
*  @param  self  a vector structure
*  @param  cmp   a pointer a comparison function
*/
void
vector_sort( vector_t *self,
int (*cmp)(const void *, const void *) );    
/**
* Create an attribute from the given parameters.
*
* @param size       number of component
* @param type       data type
* @param normalized Whether fixed-point data values should be normalized
(GL_TRUE) or converted directly as fixed-point values
(GL_FALSE) when they are  accessed.
* @param stride     byte offset between consecutive attributes.
* @param pointer    pointer to the first component of the first attribute
*                   element in the array.
* @return           a new initialized vertex attribute.
*
* @private
*/
vertex_attribute_t *
vertex_attribute_new( GLchar * name,
GLint size,
GLenum type,
GLboolean normalized,
GLsizei stride,
GLvoid *pointer );
/**
* Delete a vertex attribute.
*
* @param  self a vertex attribute
*
*/
void
vertex_attribute_delete( vertex_attribute_t * self );
/**
* Create an attribute from the given description.
*
* @param  format Format string specifies the format of a vertex attribute.
* @return        an initialized vertex attribute
*
* @private
*/
vertex_attribute_t *
vertex_attribute_parse( char *format );
/**
* Enable a vertex attribute.
*
* @param attr  a vertex attribute
*
* @private
*/
void
vertex_attribute_enable( vertex_attribute_t *attr );    
#ifdef WIN32
// strndup() is not available on Windows
char *strndup( const char *s1, size_t n);
#endif
/**
* Creates an empty vertex buffer.
*
* @param  format a string describing vertex format.
* @return        an empty vertex buffer.
*/
vertex_buffer_t *
vertex_buffer_new( const char *format );
/**
* Deletes vertex buffer and releases GPU memory.
*
* @param  self  a vertex buffer
*/
void
vertex_buffer_delete( vertex_buffer_t * self );
/**
*  Returns the number of items in the vertex buffer
*
*  @param  self  a vertex buffer
*  @return       number of items
*/
size_t
vertex_buffer_size( const vertex_buffer_t *self );
/**
*  Returns vertex format
*
*  @param  self  a vertex buffer
*  @return       vertex format
*/
const char *
vertex_buffer_format( const vertex_buffer_t *self );
/**
* Print information about a vertex buffer
*
* @param  self  a vertex buffer
*/
void
vertex_buffer_print( vertex_buffer_t * self );
/**
* Prepare vertex buffer for render.
*
* @param  self  a vertex buffer
* @param  mode  render mode
*/
void
vertex_buffer_render_setup ( vertex_buffer_t *self,
GLenum mode );
/**
* Finish rendering by setting back modified states
*
* @param  self  a vertex buffer
*/
void
vertex_buffer_render_finish ( vertex_buffer_t *self );
/**
* Render vertex buffer.
*
* @param  self  a vertex buffer
* @param  mode  render mode
*/
void
vertex_buffer_render ( vertex_buffer_t *self,
GLenum mode );
/**
* Render a specified item from the vertex buffer.
*
* @param  self   a vertex buffer
* @param  index index of the item to be rendered
*/
void
vertex_buffer_render_item ( vertex_buffer_t *self,
size_t index );
/**
* Upload buffer to GPU memory.
*
* @param  self  a vertex buffer
*/
void
vertex_buffer_upload( vertex_buffer_t *self );
/**
* Clear all items.
*
* @param  self  a vertex buffer
*/
void
vertex_buffer_clear( vertex_buffer_t *self );
/**
* Appends indices at the end of the buffer.
*
* @param  self     a vertex buffer
* @param  indices  indices to be appended
* @param  icount   number of indices to be appended
*
* @private
*/
void
vertex_buffer_push_back_indices ( vertex_buffer_t *self,
const GLuint * indices,
const size_t icount );
/**
* Appends vertices at the end of the buffer.
*
* @note Internal use
*
* @param  self     a vertex buffer
* @param  vertices vertices to be appended
* @param  vcount   number of vertices to be appended
*
* @private
*/
void
vertex_buffer_push_back_vertices ( vertex_buffer_t *self,
const void * vertices,
const size_t vcount );
/**
* Insert indices in the buffer.
*
* @param  self    a vertex buffer
* @param  index   location before which to insert indices
* @param  indices indices to be appended
* @param  icount  number of indices to be appended
*
* @private
*/
void
vertex_buffer_insert_indices ( vertex_buffer_t *self,
const size_t index,
const GLuint *indices,
const size_t icount );
/**
* Insert vertices in the buffer.
*
* @param  self     a vertex buffer
* @param  index    location before which to insert vertices
* @param  vertices vertices to be appended
* @param  vcount   number of vertices to be appended
*
* @private
*/
void
vertex_buffer_insert_vertices ( vertex_buffer_t *self,
const size_t index,
const void *vertices,
const size_t vcount );
/**
* Erase indices in the buffer.
*
* @param  self   a vertex buffer
* @param  first  the index of the first index to be erased
* @param  last   the index of the last index to be erased
*
* @private
*/
void
vertex_buffer_erase_indices ( vertex_buffer_t *self,
const size_t first,
const size_t last );
/**
* Erase vertices in the buffer.
*
* @param  self   a vertex buffer
* @param  first  the index of the first vertex to be erased
* @param  last   the index of the last vertex to be erased
*
* @private
*/
void
vertex_buffer_erase_vertices ( vertex_buffer_t *self,
const size_t first,
const size_t last );
/**
* Append a new item to the collection.
*
* @param  self   a vertex buffer
* @param  vcount   number of vertices
* @param  vertices raw vertices data
* @param  icount   number of indices
* @param  indices  raw indices data
*/
size_t
vertex_buffer_push_back( vertex_buffer_t * self,
const void * vertices, const size_t vcount,
const GLuint * indices, const size_t icount );
/**
* Insert a new item into the vertex buffer.
*
* @param  self      a vertex buffer
* @param  index     location before which to insert item
* @param  vertices  raw vertices data
* @param  vcount    number of vertices
* @param  indices   raw indices data
* @param  icount    number of indices
*/
size_t
vertex_buffer_insert( vertex_buffer_t * self,
const size_t index,
const void * vertices, const size_t vcount,
const GLuint * indices, const size_t icount );
/**
* Erase an item from the vertex buffer.
*
* @param  self     a vertex buffer
* @param  index    index of the item to be deleted
*/
void
vertex_buffer_erase( vertex_buffer_t * self,
const size_t index );    
int32_t g_borderposition_bottom;
int32_t g_borderposition_fill;
int32_t g_borderposition_left;
int32_t g_borderposition_right;
int32_t g_borderposition_top;
int32_t g_clickstate_entered;
int32_t g_clickstate_none;
int32_t g_clickstate_pressed;
int32_t g_flowlayoutorientation_bottomtop;
int32_t g_flowlayoutorientation_leftright;
int32_t g_flowlayoutorientation_rightleft;
int32_t g_flowlayoutorientation_topbottom;
int32_t g_glblendfunctype_gl_constant_alpha;
int32_t g_glblendfunctype_gl_constant_color;
int32_t g_glblendfunctype_gl_dst_alpha;
int32_t g_glblendfunctype_gl_dst_color;
int32_t g_glblendfunctype_gl_one;
int32_t g_glblendfunctype_gl_one_minus_constant_alpha;
int32_t g_glblendfunctype_gl_one_minus_constant_color;
int32_t g_glblendfunctype_gl_one_minus_dst_alpha;
int32_t g_glblendfunctype_gl_one_minus_dst_color;
int32_t g_glblendfunctype_gl_one_minus_src_alpha;
int32_t g_glblendfunctype_gl_one_minus_src_color;
int32_t g_glblendfunctype_gl_src_alpha;
int32_t g_glblendfunctype_gl_src_alpha_saturate;
int32_t g_glblendfunctype_gl_src_color;
int32_t g_glblendfunctype_gl_zero;
int32_t g_gldrawmode_gl_line_loop;
int32_t g_gldrawmode_gl_line_strip;
int32_t g_gldrawmode_gl_lines;
int32_t g_gldrawmode_gl_points;
int32_t g_gldrawmode_gl_triangle_fan;
int32_t g_gldrawmode_gl_triangle_strip;
int32_t g_gldrawmode_gl_triangles;
int32_t g_glfeature_gl_blend;
int32_t g_glfeature_gl_cull_face;
int32_t g_glfeature_gl_depth_test;
int32_t g_glfeature_gl_dither;
int32_t g_glfeature_gl_polygon_offset_fill;
int32_t g_glfeature_gl_sample_alpha_to_coverage;
int32_t g_glfeature_gl_sample_coverage;
int32_t g_glfeature_gl_scissor_test;
int32_t g_glfeature_gl_stencil_test;
int32_t g_glframebufferattachment_gl_color_attachment0;
int32_t g_glframebufferattachment_gl_depth_attachment;
int32_t g_glframebufferattachment_gl_stencil_attachment;
int32_t g_glframebufferstatus_gl_framebuffer_complete;
int32_t g_glframebufferstatus_gl_framebuffer_incomplete_attachment;
int32_t g_glframebufferstatus_gl_framebuffer_incomplete_missing_attachment;
int32_t g_glframebufferstatus_gl_framebuffer_unsupported;
int32_t g_glframebuffertexture_gl_texture_2d;
int32_t g_glframebuffertexture_gl_texture_cube_map_negative_x;
int32_t g_glframebuffertexture_gl_texture_cube_map_negative_y;
int32_t g_glframebuffertexture_gl_texture_cube_map_negative_z;
int32_t g_glframebuffertexture_gl_texture_cube_map_positive_x;
int32_t g_glframebuffertexture_gl_texture_cube_map_positive_y;
int32_t g_glframebuffertexture_gl_texture_cube_map_positive_z;
int32_t g_glrenderbufferformat_gl_depth_component16;
int32_t g_glrenderbufferformat_gl_rgb565;
int32_t g_glrenderbufferformat_gl_rgb5_a1;
int32_t g_glrenderbufferformat_gl_rgba4;
int32_t g_glrenderbufferformat_gl_stencil_index8;
int32_t g_gltexture_gl_texture_2d;
int32_t g_gltexture_gl_texture_cube_map;
int32_t g_gltextureattribute_gl_texture_mag_filter;
int32_t g_gltextureattribute_gl_texture_min_filter;
int32_t g_gltextureattribute_gl_texture_wrap_s;
int32_t g_gltextureattribute_gl_texture_wrap_t;
int32_t g_gltextureformat_gl_alpha;
int32_t g_gltextureformat_gl_luminance;
int32_t g_gltextureformat_gl_luminance_alpha;
int32_t g_gltextureformat_gl_rgb;
int32_t g_gltextureformat_gl_rgba;
int32_t g_gltexturetype_gl_unsigned_byte;
int32_t g_gltexturetype_gl_unsigned_short_4_4_4_4;
int32_t g_gltexturetype_gl_unsigned_short_5_5_5_1;
int32_t g_gltexturetype_gl_unsigned_short_5_6_5;
int32_t g_gltexturevalue_gl_clamp_to_edge;
int32_t g_gltexturevalue_gl_linear;
int32_t g_gltexturevalue_gl_linear_mipmap_linear;
int32_t g_gltexturevalue_gl_linear_mipmap_nearest;
int32_t g_gltexturevalue_gl_mirrored_repeat;
int32_t g_gltexturevalue_gl_nearest;
int32_t g_gltexturevalue_gl_nearest_mipmap_linear;
int32_t g_gltexturevalue_gl_nearest_mipmap_nearest;
int32_t g_gltexturevalue_gl_repeat;
int32_t g_gridunittype_fixed;
int32_t g_gridunittype_star;
int32_t g_imagestretch_aspectratio;
int32_t g_imagestretch_center;
int32_t g_imagestretch_fill;
int32_t g_listlayoutorientation_bottomtop;
int32_t g_listlayoutorientation_leftright;
int32_t g_listlayoutorientation_rightleft;
int32_t g_listlayoutorientation_topbottom;
int32_t g_loglevel_debug;
int32_t g_loglevel_error;
int32_t g_loglevel_fatal;
int32_t g_loglevel_info;
int32_t g_loglevel_trace;
int32_t g_loglevel_warn;
int32_t g_mouseeventtype_down;
int32_t g_mouseeventtype_move;
int32_t g_mouseeventtype_up;
int32_t g_texthorizontal_center;
int32_t g_texthorizontal_left;
int32_t g_texthorizontal_right;
int32_t g_textvertical_bottom;
int32_t g_textvertical_center;
int32_t g_textvertical_top;

sjs_vec4 g_a_light = { -1 };
sjs_animator g_animator = { -1 };
sjs_shader g_blurhorizontalshader = { -1 };
sjs_shader g_blurverticalshader = { -1 };
sjs_shader g_boxshader = { -1 };
int32_t g_clocks_per_sec;
sjs_color g_colors_black = { -1 };
sjs_color g_colors_blue = { -1 };
sjs_color g_colors_gray = { -1 };
sjs_color g_colors_green = { -1 };
sjs_color g_colors_red = { -1 };
sjs_color g_colors_white = { -1 };
int32_t g_dots;
int32_t g_dotsscale;
sjs_hash_string_weak_iface_element g_elementsbyid = { -1 };
void* g_emptystringdata;
float g_f32_pi;
sjs_shader g_fadeshader = { -1 };
sjs_hash_fontkey_weak_font g_fonthash = { -1 };
sjs_list_u32 g_glframebuffers = { -1 };
sjs_list_rect g_glviewports = { -1 };
int32_t g_height;
int32_t g_i32_maxvalue;
int32_t g_i32_minvalue;
sjs_shader g_imageshader = { -1 };
int32_t g_img_dots;
int32_t g_img_dotsscale;
sjs_vec4 g_l_pos = { -1 };
sjs_log g_log = { -1 };
sjs_hash_type_bool g_log_excludeall = { -1 };
sjs_hash_type_bool g_log_includeall = { -1 };
sjs_rect g_looplastrect = { -1 };
int32_t g_mainloop_frames;
int32_t g_mainloop_lasttick;
bool g_mainloop_shouldcontinue;
bool g_mainloop_showfps;
sjs_array_bool g_mainrot = { -1 };
sjs_hash_string_weak_iface_model g_modelsbyid = { -1 };
sji_element g_mouse_captureelement = { 0 };
int32_t g_oncept;
float g_persp;
sjs_shader g_phongcolorshader = { -1 };
sjs_shader g_phongtextureshader = { -1 };
sji_element g_root = { 0 };
sjs_scene2d g_rootscene = { -1 };
sjs_windowrenderer g_rootwindowrenderer = { -1 };
float g_rotateradius;
sjs_vec4 g_s_light = { -1 };
sjs_shader g_saturateshader = { -1 };
float g_scale;
sjs_array_bool g_stateof = { -1 };
sjs_array_bool g_stateofdir = { -1 };
sjs_style g_style = { -1 };
sjs_shader g_textshader = { -1 };
uint32_t g_u32_maxvalue;
sjs_string g_vertex_location_texture_normal_format = { -1 };
int32_t g_width;
int32_t result1;
float result2;
sjs_array_f32 sjt_call10 = { -1 };
sjs_array_f32 sjt_call11 = { -1 };
sjs_array_f32 sjt_call12 = { -1 };
sjs_array_f32 sjt_call13 = { -1 };
sjs_array_f32 sjt_call14 = { -1 };
sjs_array_f32 sjt_call15 = { -1 };
sjs_array_f32 sjt_call16 = { -1 };
sjs_array_f32 sjt_call17 = { -1 };
sjs_array_f32 sjt_call18 = { -1 };
sjs_array_f32 sjt_call19 = { -1 };
sjs_array_f32 sjt_call20 = { -1 };
sjs_array_f32 sjt_call21 = { -1 };
sjs_array_f32 sjt_call22 = { -1 };
sjs_array_f32 sjt_call23 = { -1 };
sjs_array_f32 sjt_call24 = { -1 };
sjs_array_f32 sjt_call25 = { -1 };
sjs_size sjt_call26 = { -1 };
sjs_test sjt_call3 = { -1 };
sjs_array_f32 sjt_call4 = { -1 };
sjs_array_f32 sjt_call5 = { -1 };
sjs_array_f32 sjt_call6 = { -1 };
sjs_array_f32 sjt_call7 = { -1 };
sjs_array_f32 sjt_call8 = { -1 };
sjs_array_f32 sjt_call9 = { -1 };
float sjt_cast2;
int32_t sjt_cast3;
float sjt_cast4;
int32_t sjt_cast5;
sjs_test* sjt_cast6 = 0;
int32_t sjt_functionParam12;
bool sjt_functionParam13;
int32_t sjt_functionParam14;
bool sjt_functionParam15;
int32_t sjt_functionParam16;
bool sjt_functionParam17;
int32_t sjt_functionParam18;
bool sjt_functionParam19;
int32_t sjt_functionParam20;
bool sjt_functionParam21;
int32_t sjt_functionParam22;
bool sjt_functionParam23;
int32_t sjt_functionParam24;
bool sjt_functionParam25;
int32_t sjt_functionParam26;
bool sjt_functionParam27;
float sjt_functionParam460;
float sjt_functionParam461;
float sjt_functionParam462;
float sjt_functionParam463;
float sjt_functionParam464;
float sjt_functionParam465;
float sjt_functionParam466;
float sjt_functionParam467;
float sjt_functionParam468;
float sjt_functionParam469;
float sjt_functionParam470;
float sjt_functionParam471;
float sjt_functionParam472;
float sjt_functionParam473;
float sjt_functionParam474;
float sjt_functionParam475;
float sjt_functionParam476;
float sjt_functionParam477;
float sjt_functionParam478;
float sjt_functionParam479;
float sjt_functionParam480;
float sjt_functionParam481;
sjs_size* sjt_functionParam482 = 0;
sjs_array_bool* sjt_parent10 = 0;
sjs_array_bool* sjt_parent11 = 0;
sjs_array_f32* sjt_parent163 = 0;
sjs_array_f32* sjt_parent164 = 0;
sjs_array_f32* sjt_parent165 = 0;
sjs_array_f32* sjt_parent166 = 0;
sjs_array_f32* sjt_parent167 = 0;
sjs_array_f32* sjt_parent168 = 0;
sjs_array_f32* sjt_parent169 = 0;
sjs_array_f32* sjt_parent170 = 0;
sjs_array_f32* sjt_parent171 = 0;
sjs_array_f32* sjt_parent172 = 0;
sjs_array_f32* sjt_parent173 = 0;
sjs_array_f32* sjt_parent174 = 0;
sjs_array_f32* sjt_parent175 = 0;
sjs_array_f32* sjt_parent176 = 0;
sjs_array_f32* sjt_parent177 = 0;
sjs_array_f32* sjt_parent178 = 0;
sjs_array_f32* sjt_parent179 = 0;
sjs_array_f32* sjt_parent180 = 0;
sjs_array_f32* sjt_parent181 = 0;
sjs_array_f32* sjt_parent182 = 0;
sjs_array_f32* sjt_parent183 = 0;
sjs_array_f32* sjt_parent184 = 0;
sjs_windowrenderer* sjt_parent185 = 0;
sjs_array_bool* sjt_parent4 = 0;
sjs_array_bool* sjt_parent5 = 0;
sjs_array_bool* sjt_parent6 = 0;
sjs_array_bool* sjt_parent7 = 0;
sjs_array_bool* sjt_parent8 = 0;
sjs_array_bool* sjt_parent9 = 0;
sjs_hash_type_bool sjt_value1 = { -1 };

void sjf_animator(sjs_animator* _this);
void sjf_animator_copy(sjs_animator* _this, sjs_animator* _from);
void sjf_animator_destroy(sjs_animator* _this);
void sjf_animator_heap(sjs_animator* _this);
void sjf_animator_nextframe(sjs_animator* _parent, int32_t time);
void sjf_array_bool(sjs_array_bool* _this);
void sjf_array_bool_copy(sjs_array_bool* _this, sjs_array_bool* _from);
void sjf_array_bool_destroy(sjs_array_bool* _this);
void sjf_array_bool_getat(sjs_array_bool* _parent, int32_t index, bool* _return);
void sjf_array_bool_heap(sjs_array_bool* _this);
void sjf_array_bool_initat(sjs_array_bool* _parent, int32_t index, bool item);
void sjf_array_bool_setat(sjs_array_bool* _parent, int32_t index, bool item);
void sjf_array_char(sjs_array_char* _this);
void sjf_array_char_copy(sjs_array_char* _this, sjs_array_char* _from);
void sjf_array_char_destroy(sjs_array_char* _this);
void sjf_array_char_getat(sjs_array_char* _parent, int32_t index, char* _return);
void sjf_array_char_grow(sjs_array_char* _parent, int32_t newsize, sjs_array_char* _return);
void sjf_array_char_grow_heap(sjs_array_char* _parent, int32_t newsize, sjs_array_char** _return);
void sjf_array_char_heap(sjs_array_char* _this);
void sjf_array_char_initat(sjs_array_char* _parent, int32_t index, char item);
void sjf_array_char_isequal(sjs_array_char* _parent, sjs_array_char* test, bool* _return);
void sjf_array_f32(sjs_array_f32* _this);
void sjf_array_f32_copy(sjs_array_f32* _this, sjs_array_f32* _from);
void sjf_array_f32_destroy(sjs_array_f32* _this);
void sjf_array_f32_getat(sjs_array_f32* _parent, int32_t index, float* _return);
void sjf_array_f32_heap(sjs_array_f32* _this);
void sjf_array_f32_init(sjs_array_f32* _parent, float item, sjs_array_f32* _return);
void sjf_array_f32_init_heap(sjs_array_f32* _parent, float item, sjs_array_f32** _return);
void sjf_array_f32_setat(sjs_array_f32* _parent, int32_t index, float item);
void sjf_array_heap_iface_animation(sjs_array_heap_iface_animation* _this);
void sjf_array_heap_iface_animation_copy(sjs_array_heap_iface_animation* _this, sjs_array_heap_iface_animation* _from);
void sjf_array_heap_iface_animation_destroy(sjs_array_heap_iface_animation* _this);
void sjf_array_heap_iface_animation_getat_heap(sjs_array_heap_iface_animation* _parent, int32_t index, sji_animation* _return);
void sjf_array_heap_iface_animation_heap(sjs_array_heap_iface_animation* _this);
void sjf_array_heap_iface_model(sjs_array_heap_iface_model* _this);
void sjf_array_heap_iface_model_copy(sjs_array_heap_iface_model* _this, sjs_array_heap_iface_model* _from);
void sjf_array_heap_iface_model_destroy(sjs_array_heap_iface_model* _this);
void sjf_array_heap_iface_model_heap(sjs_array_heap_iface_model* _this);
void sjf_array_rect(sjs_array_rect* _this);
void sjf_array_rect_copy(sjs_array_rect* _this, sjs_array_rect* _from);
void sjf_array_rect_destroy(sjs_array_rect* _this);
void sjf_array_rect_getat(sjs_array_rect* _parent, int32_t index, sjs_rect* _return);
void sjf_array_rect_getat_heap(sjs_array_rect* _parent, int32_t index, sjs_rect** _return);
void sjf_array_rect_grow(sjs_array_rect* _parent, int32_t newsize, sjs_array_rect* _return);
void sjf_array_rect_grow_heap(sjs_array_rect* _parent, int32_t newsize, sjs_array_rect** _return);
void sjf_array_rect_heap(sjs_array_rect* _this);
void sjf_array_rect_initat(sjs_array_rect* _parent, int32_t index, sjs_rect* item);
void sjf_array_u32(sjs_array_u32* _this);
void sjf_array_u32_copy(sjs_array_u32* _this, sjs_array_u32* _from);
void sjf_array_u32_destroy(sjs_array_u32* _this);
void sjf_array_u32_heap(sjs_array_u32* _this);
void sjf_color(sjs_color* _this);
void sjf_color_copy(sjs_color* _this, sjs_color* _from);
void sjf_color_destroy(sjs_color* _this);
void sjf_color_heap(sjs_color* _this);
void sjf_debug_writeline(sjs_string* data);
void sjf_f32_abs(float v, float* _return);
void sjf_f32_asstring(float val, sjs_string* _return);
void sjf_f32_asstring_heap(float val, sjs_string** _return);
void sjf_f32_cos(float v, float* _return);
void sjf_f32_exp(float v, float* _return);
void sjf_f32_hash(float val, uint32_t* _return);
void sjf_f32_pow(float x, float y, float* _return);
void sjf_f32_sin(float v, float* _return);
void sjf_f32_sqrt(float v, float* _return);
void sjf_f32_tan(float v, float* _return);
void sjf_font(sjs_font* _this);
void sjf_font_copy(sjs_font* _this, sjs_font* _from);
void sjf_font_destroy(sjs_font* _this);
void sjf_font_heap(sjs_font* _this);
void sjf_fontkey(sjs_fontkey* _this);
void sjf_fontkey_copy(sjs_fontkey* _this, sjs_fontkey* _from);
void sjf_fontkey_destroy(sjs_fontkey* _this);
void sjf_fontkey_hash(sjs_fontkey* _parent, uint32_t* _return);
void sjf_fontkey_heap(sjs_fontkey* _this);
void sjf_fontkey_isequal(sjs_fontkey* _parent, sjs_fontkey* x, bool* _return);
void sjf_glbeginpoints(void);
void sjf_glblendfunc(int32_t sfactor, int32_t dfactor);
void sjf_glclearcolor(sjs_color* color);
void sjf_glcolor3f(float r, float g, float b);
void sjf_glenable(int32_t feature);
void sjf_glend(void);
void sjf_glpopviewport(sjs_rect* rect, sjs_rect* scenerect);
void sjf_glpushviewport(sjs_rect* rect, sjs_rect* scenerect);
void sjf_glrotated(float r, float x, float y, float z);
void sjf_glvertex3f(float x, float y, float z);
void sjf_halt(sjs_string* reason);
void sjf_hash_fontkey_weak_font(sjs_hash_fontkey_weak_font* _this);
void sjf_hash_fontkey_weak_font__weakptrremovekey(sjs_hash_fontkey_weak_font* _parent, sjs_fontkey* key);
void sjf_hash_fontkey_weak_font__weakptrremovevalue(sjs_hash_fontkey_weak_font* _parent, sjs_font* val);
void sjf_hash_fontkey_weak_font_copy(sjs_hash_fontkey_weak_font* _this, sjs_hash_fontkey_weak_font* _from);
void sjf_hash_fontkey_weak_font_destroy(sjs_hash_fontkey_weak_font* _this);
void sjf_hash_fontkey_weak_font_heap(sjs_hash_fontkey_weak_font* _this);
void sjf_hash_string_weak_iface_element(sjs_hash_string_weak_iface_element* _this);
void sjf_hash_string_weak_iface_element__weakptrremovekey(sjs_hash_string_weak_iface_element* _parent, sjs_string* key);
void sjf_hash_string_weak_iface_element__weakptrremovevalue(sjs_hash_string_weak_iface_element* _parent, sji_element val);
void sjf_hash_string_weak_iface_element_copy(sjs_hash_string_weak_iface_element* _this, sjs_hash_string_weak_iface_element* _from);
void sjf_hash_string_weak_iface_element_destroy(sjs_hash_string_weak_iface_element* _this);
void sjf_hash_string_weak_iface_element_heap(sjs_hash_string_weak_iface_element* _this);
void sjf_hash_string_weak_iface_model(sjs_hash_string_weak_iface_model* _this);
void sjf_hash_string_weak_iface_model__weakptrremovekey(sjs_hash_string_weak_iface_model* _parent, sjs_string* key);
void sjf_hash_string_weak_iface_model__weakptrremovevalue(sjs_hash_string_weak_iface_model* _parent, sji_model val);
void sjf_hash_string_weak_iface_model_copy(sjs_hash_string_weak_iface_model* _this, sjs_hash_string_weak_iface_model* _from);
void sjf_hash_string_weak_iface_model_destroy(sjs_hash_string_weak_iface_model* _this);
void sjf_hash_string_weak_iface_model_heap(sjs_hash_string_weak_iface_model* _this);
void sjf_hash_type_bool(sjs_hash_type_bool* _this);
void sjf_hash_type_bool__weakptrremovekey(sjs_hash_type_bool* _parent, int32_t key);
void sjf_hash_type_bool__weakptrremovevalue(sjs_hash_type_bool* _parent, bool val);
void sjf_hash_type_bool_copy(sjs_hash_type_bool* _this, sjs_hash_type_bool* _from);
void sjf_hash_type_bool_destroy(sjs_hash_type_bool* _this);
void sjf_hash_type_bool_heap(sjs_hash_type_bool* _this);
void sjf_i32_max(int32_t a, int32_t b, int32_t* _return);
void sjf_light(sjs_light* _this);
void sjf_light_copy(sjs_light* _this, sjs_light* _from);
void sjf_light_destroy(sjs_light* _this);
void sjf_light_heap(sjs_light* _this);
void sjf_list_heap_iface_animation(sjs_list_heap_iface_animation* _this);
void sjf_list_heap_iface_animation_copy(sjs_list_heap_iface_animation* _this, sjs_list_heap_iface_animation* _from);
void sjf_list_heap_iface_animation_destroy(sjs_list_heap_iface_animation* _this);
void sjf_list_heap_iface_animation_getat_heap(sjs_list_heap_iface_animation* _parent, int32_t index, sji_animation* _return);
void sjf_list_heap_iface_animation_getcount(sjs_list_heap_iface_animation* _parent, int32_t* _return);
void sjf_list_heap_iface_animation_heap(sjs_list_heap_iface_animation* _this);
void sjf_list_heap_iface_animation_removeat(sjs_list_heap_iface_animation* _parent, int32_t index);
void sjf_list_heap_iface_model(sjs_list_heap_iface_model* _this);
void sjf_list_heap_iface_model_copy(sjs_list_heap_iface_model* _this, sjs_list_heap_iface_model* _from);
void sjf_list_heap_iface_model_destroy(sjs_list_heap_iface_model* _this);
void sjf_list_heap_iface_model_heap(sjs_list_heap_iface_model* _this);
void sjf_list_rect(sjs_list_rect* _this);
void sjf_list_rect_add(sjs_list_rect* _parent, sjs_rect* item);
void sjf_list_rect_copy(sjs_list_rect* _this, sjs_list_rect* _from);
void sjf_list_rect_destroy(sjs_list_rect* _this);
void sjf_list_rect_getat(sjs_list_rect* _parent, int32_t index, sjs_rect* _return);
void sjf_list_rect_getat_heap(sjs_list_rect* _parent, int32_t index, sjs_rect** _return);
void sjf_list_rect_getcount(sjs_list_rect* _parent, int32_t* _return);
void sjf_list_rect_heap(sjs_list_rect* _this);
void sjf_list_rect_removeat(sjs_list_rect* _parent, int32_t index);
void sjf_list_u32(sjs_list_u32* _this);
void sjf_list_u32_copy(sjs_list_u32* _this, sjs_list_u32* _from);
void sjf_list_u32_destroy(sjs_list_u32* _this);
void sjf_list_u32_heap(sjs_list_u32* _this);
void sjf_log(sjs_log* _this);
void sjf_log_copy(sjs_log* _this, sjs_log* _from);
void sjf_log_destroy(sjs_log* _this);
void sjf_log_heap(sjs_log* _this);
void sjf_mainloop(void);
void sjf_mat4(sjs_mat4* _this);
void sjf_mat4_copy(sjs_mat4* _this, sjs_mat4* _from);
void sjf_mat4_destroy(sjs_mat4* _this);
void sjf_mat4_heap(sjs_mat4* _this);
void sjf_mat4_identity(sjs_mat4* _return);
void sjf_mat4_identity_heap(sjs_mat4** _return);
void sjf_mat4_orthographic(float left, float right, float bottom, float top, float znear, float zfar, sjs_mat4* _return);
void sjf_mat4_orthographic_heap(float left, float right, float bottom, float top, float znear, float zfar, sjs_mat4** _return);
void sjf_mat4_scale(float x, float y, float z, sjs_mat4* _return);
void sjf_mat4_scale_heap(float x, float y, float z, sjs_mat4** _return);
void sjf_mouseevent(sjs_mouseevent* _this);
void sjf_mouseevent_copy(sjs_mouseevent* _this, sjs_mouseevent* _from);
void sjf_mouseevent_destroy(sjs_mouseevent* _this);
void sjf_mouseevent_heap(sjs_mouseevent* _this);
void sjf_point(sjs_point* _this);
void sjf_point_copy(sjs_point* _this, sjs_point* _from);
void sjf_point_destroy(sjs_point* _this);
void sjf_point_heap(sjs_point* _this);
void sjf_rect(sjs_rect* _this);
void sjf_rect_copy(sjs_rect* _this, sjs_rect* _from);
void sjf_rect_destroy(sjs_rect* _this);
void sjf_rect_heap(sjs_rect* _this);
void sjf_rect_isequal(sjs_rect* _parent, sjs_rect* rect, bool* _return);
void sjf_runloop(void);
void sjf_scene2d(sjs_scene2d* _this);
void sjf_scene2d_copy(sjs_scene2d* _this, sjs_scene2d* _from);
void sjf_scene2d_destroy(sjs_scene2d* _this);
void sjf_scene2d_end(sjs_scene2d* _parent);
void sjf_scene2d_heap(sjs_scene2d* _this);
void sjf_scene2d_setsize(sjs_scene2d* _parent, sjs_size* size);
void sjf_scene2d_start(sjs_scene2d* _parent);
void sjf_shader(sjs_shader* _this);
void sjf_shader_copy(sjs_shader* _this, sjs_shader* _from);
void sjf_shader_destroy(sjs_shader* _this);
void sjf_shader_heap(sjs_shader* _this);
void sjf_size(sjs_size* _this);
void sjf_size_copy(sjs_size* _this, sjs_size* _from);
void sjf_size_destroy(sjs_size* _this);
void sjf_size_heap(sjs_size* _this);
void sjf_size_isequal(sjs_size* _parent, sjs_size* size, bool* _return);
void sjf_string(sjs_string* _this);
void sjf_string_add(sjs_string* _parent, sjs_string* item, sjs_string* _return);
void sjf_string_add_heap(sjs_string* _parent, sjs_string* item, sjs_string** _return);
void sjf_string_copy(sjs_string* _this, sjs_string* _from);
void sjf_string_destroy(sjs_string* _this);
void sjf_string_getat(sjs_string* _parent, int32_t index, char* _return);
void sjf_string_hash(sjs_string* _parent, uint32_t* _return);
void sjf_string_heap(sjs_string* _this);
void sjf_string_isequal(sjs_string* _parent, sjs_string* test, bool* _return);
void sjf_string_nullterminate(sjs_string* _parent);
void sjf_style(sjs_style* _this);
void sjf_style_copy(sjs_style* _this, sjs_style* _from);
void sjf_style_destroy(sjs_style* _this);
void sjf_style_heap(sjs_style* _this);
void sjf_test(sjs_test* _this);
void sjf_test_as_sji_element(sjs_test* _this, sji_element* _return);
void sjf_test_asinterface(sjs_test* _this, int typeId, sjs_interface* _return);
void sjf_test_calculate(sjs_test* _parent);
void sjf_test_copy(sjs_test* _this, sjs_test* _from);
void sjf_test_destroy(sjs_test* _this);
void sjf_test_findaxis(sjs_test* _parent);
void sjf_test_firemouseevent(sjs_test* _parent, sjs_mouseevent* mouseevent, bool* _return);
void sjf_test_getclasstype(sjs_object* _this, int* _return);
void sjf_test_getrect(sjs_test* _parent, sjs_rect* _return);
void sjf_test_getrect_heap(sjs_test* _parent, sjs_rect** _return);
void sjf_test_getsize(sjs_test* _parent, sjs_size* maxsize, sjs_size* _return);
void sjf_test_getsize_heap(sjs_test* _parent, sjs_size* maxsize, sjs_size** _return);
void sjf_test_gett(sjs_test* _parent, int32_t xpi, int32_t n, float* _return);
void sjf_test_gettm(sjs_test* _parent, int32_t xpi, int32_t n, float* _return);
void sjf_test_heap(sjs_test* _this);
void sjf_test_img_gettm(sjs_test* _parent, int32_t xpi, int32_t n, float* _return);
void sjf_test_imgdata_functionlist(sjs_test* _parent);
void sjf_test_render(sjs_test* _parent, sjs_scene2d* scene);
void sjf_test_setrect(sjs_test* _parent, sjs_rect* rect_);
void sjf_type_hash(int32_t val, uint32_t* _return);
void sjf_type_isequal(int32_t l, int32_t r, bool* _return);
void sjf_vec3(sjs_vec3* _this);
void sjf_vec3_copy(sjs_vec3* _this, sjs_vec3* _from);
void sjf_vec3_destroy(sjs_vec3* _this);
void sjf_vec3_heap(sjs_vec3* _this);
void sjf_vec4(sjs_vec4* _this);
void sjf_vec4_copy(sjs_vec4* _this, sjs_vec4* _from);
void sjf_vec4_destroy(sjs_vec4* _this);
void sjf_vec4_heap(sjs_vec4* _this);
void sjf_windowrender_disablevsync(void);
void sjf_windowrenderer(sjs_windowrenderer* _this);
void sjf_windowrenderer_copy(sjs_windowrenderer* _this, sjs_windowrenderer* _from);
void sjf_windowrenderer_destroy(sjs_windowrenderer* _this);
void sjf_windowrenderer_getsize(sjs_windowrenderer* _parent, sjs_size* _return);
void sjf_windowrenderer_getsize_heap(sjs_windowrenderer* _parent, sjs_size** _return);
void sjf_windowrenderer_heap(sjs_windowrenderer* _this);
void sjf_windowrenderer_present(sjs_windowrenderer* _parent);
void sjf_windowrenderer_setsize(sjs_windowrenderer* _parent, sjs_size* s);
void main_destroy(void);

#ifndef type_bool_hash_function
#define type_bool_hash_function
#if false
KHASH_INIT_FUNCTION_DEREF(type_bool_hash_type, int32_t, bool, 1, sjf_type_hash, sjf_type_isequal)
#else
KHASH_INIT_FUNCTION(type_bool_hash_type, int32_t, bool, 1, sjf_type_hash, sjf_type_isequal)
#endif
#endif
#ifndef type_bool_hash_function
#define type_bool_hash_function
#if false
KHASH_INIT_FUNCTION_DEREF(type_bool_hash_type, int32_t, bool, 1, sjf_type_hash, sjf_type_isequal)
#else
KHASH_INIT_FUNCTION(type_bool_hash_type, int32_t, bool, 1, sjf_type_hash, sjf_type_isequal)
#endif
#endif
#include <lib/common/common.c>
#ifndef string_weak_iface_model_hash_function
#define string_weak_iface_model_hash_function
#if true
KHASH_INIT_FUNCTION_DEREF(string_weak_iface_model_hash_type, sjs_string, sji_model, 1, sjf_string_hash, sjf_string_isequal)
#else
KHASH_INIT_FUNCTION(string_weak_iface_model_hash_type, sjs_string, sji_model, 1, sjf_string_hash, sjf_string_isequal)
#endif
#endif
#ifndef string_weak_iface_model_hash_function
#define string_weak_iface_model_hash_function
#if true
KHASH_INIT_FUNCTION_DEREF(string_weak_iface_model_hash_type, sjs_string, sji_model, 1, sjf_string_hash, sjf_string_isequal)
#else
KHASH_INIT_FUNCTION(string_weak_iface_model_hash_type, sjs_string, sji_model, 1, sjf_string_hash, sjf_string_isequal)
#endif
#endif
#ifndef string_weak_iface_element_hash_function
#define string_weak_iface_element_hash_function
#if true
KHASH_INIT_FUNCTION_DEREF(string_weak_iface_element_hash_type, sjs_string, sji_element, 1, sjf_string_hash, sjf_string_isequal)
#else
KHASH_INIT_FUNCTION(string_weak_iface_element_hash_type, sjs_string, sji_element, 1, sjf_string_hash, sjf_string_isequal)
#endif
#endif
#ifndef string_weak_iface_element_hash_function
#define string_weak_iface_element_hash_function
#if true
KHASH_INIT_FUNCTION_DEREF(string_weak_iface_element_hash_type, sjs_string, sji_element, 1, sjf_string_hash, sjf_string_isequal)
#else
KHASH_INIT_FUNCTION(string_weak_iface_element_hash_type, sjs_string, sji_element, 1, sjf_string_hash, sjf_string_isequal)
#endif
#endif
double *
make_distance_mapd( double *data, unsigned int width, unsigned int height )
{
    short * xdist = (short *)  malloc( width * height * sizeof(short) );
    short * ydist = (short *)  malloc( width * height * sizeof(short) );
    double * gx   = (double *) calloc( width * height, sizeof(double) );
    double * gy      = (double *) calloc( width * height, sizeof(double) );
    double * outside = (double *) calloc( width * height, sizeof(double) );
    double * inside  = (double *) calloc( width * height, sizeof(double) );
    double vmin = DBL_MAX;
    unsigned int i;
    // Compute outside = edtaa3(bitmap); % Transform background (0's)
    computegradient( data, width, height, gx, gy);
    edtaa3(data, gx, gy, width, height, xdist, ydist, outside);
    for( i=0; i<width*height; ++i)
    if( outside[i] < 0.0 )
    outside[i] = 0.0;
    // Compute inside = edtaa3(1-bitmap); % Transform foreground (1's)
    memset( gx, 0, sizeof(double)*width*height );
    memset( gy, 0, sizeof(double)*width*height );
    for( i=0; i<width*height; ++i)
    data[i] = 1 - data[i];
    computegradient( data, width, height, gx, gy );
    edtaa3( data, gx, gy, width, height, xdist, ydist, inside );
    for( i=0; i<width*height; ++i )
    if( inside[i] < 0 )
    inside[i] = 0.0;
    // distmap = outside - inside; % Bipolar distance field
    for( i=0; i<width*height; ++i)
    {
        outside[i] -= inside[i];
        if( outside[i] < vmin )
        vmin = outside[i];
    }
    vmin = fabs(vmin);
    for( i=0; i<width*height; ++i)
    {
        double v = outside[i];
        if     ( v < -vmin) outside[i] = -vmin;
        else if( v > +vmin) outside[i] = +vmin;
        data[i] = (outside[i]+vmin)/(2*vmin);
    }
    free( xdist );
    free( ydist );
    free( gx );
    free( gy );
    free( outside );
    free( inside );
    return data;
}
unsigned char *
make_distance_mapb( unsigned char *img,
unsigned int width, unsigned int height )
{
    double * data    = (double *) calloc( width * height, sizeof(double) );
    unsigned char *out = (unsigned char *) malloc( width * height * sizeof(unsigned char) );
    unsigned int i;
    // find minimimum and maximum values
    double img_min = DBL_MAX;
    double img_max = DBL_MIN;
    for( i=0; i<width*height; ++i)
    {
        double v = img[i];
        data[i] = v;
        if (v > img_max)
        img_max = v;
        if (v < img_min)
        img_min = v;
    }
    // Map values from 0 - 255 to 0.0 - 1.0
    for( i=0; i<width*height; ++i)
    data[i] = (img[i]-img_min)/img_max;
    data = make_distance_mapd(data, width, height);
    // map values from 0.0 - 1.0 to 0 - 255
    for( i=0; i<width*height; ++i)
    out[i] = (unsigned char)(255*(1-data[i]));
    free( data );
    return out;
}
/*
* Compute the local gradient at edge pixels using convolution filters.
* The gradient is computed only at edge pixels. At other places in the
* image, it is never used, and it's mostly zero anyway.
*/
void computegradient(double *img, int w, int h, double *gx, double *gy)
{
    int i,j,k;
    double glength;
    #define SQRT2 1.4142136
    // Avoid edges where the kernels would spill over
    for(i = 1; i < h-1; i++) {
        for(j = 1; j < w-1; j++) {
            k = i*w + j;
            // Compute gradient for edge pixels only
            if((img[k]>0.0) && (img[k]<1.0)) {
                gx[k] = -img[k-w-1] - SQRT2*img[k-1] - img[k+w-1] + img[k-w+1] + SQRT2*img[k+1] + img[k+w+1];
                gy[k] = -img[k-w-1] - SQRT2*img[k-w] - img[k-w+1] + img[k+w-1] + SQRT2*img[k+w] + img[k+w+1];
                glength = gx[k]*gx[k] + gy[k]*gy[k];
                if(glength > 0.0) {
                    // Avoid division by zero
                    glength = sqrt(glength);
                    gx[k]=gx[k]/glength;
                    gy[k]=gy[k]/glength;
                }
            }
        }
    }
    // TODO: Compute reasonable values for gx, gy also around the image edges.
    // (These are zero now, which reduces the accuracy for a 1-pixel wide region
    // around the image edge.) 2x2 kernels would be suitable for this.
}
/*
* A somewhat tricky function to approximate the distance to an edge in a
* certain pixel, with consideration to either the local gradient (gx,gy)
* or the direction to the pixel (dx,dy) and the pixel greyscale value a.
* The latter alternative, using (dx,dy), is the metric used by edtaa2().
* Using a local estimate of the edge gradient (gx,gy) yields much better
* accuracy at and near edges, and reduces the error even at distant pixels
* provided that the gradient direction is accurately estimated.
*/
double edgedf(double gx, double gy, double a)
{
    double df, glength, temp, a1;
    // Either A) gu or gv are zero, or B) both
    if ((gx == 0) || (gy == 0)) {
        // Linear approximation is A) correct or B) a fair guess
        df = 0.5-a;  
    } else {
        glength = sqrt(gx*gx + gy*gy);
        if(glength>0) {
            gx = gx/glength;
            gy = gy/glength;
        }
        /* Everything is symmetric wrt sign and transposition,
        * so move to first octant (gx>=0, gy>=0, gx>=gy) to
        * avoid handling all possible edge directions.
        */
        gx = fabs(gx);
        gy = fabs(gy);
        if(gx<gy) {
            temp = gx;
            gx = gy;
            gy = temp;
        }
        a1 = 0.5*gy/gx;
        if (a < a1) {
            // 0 <= a < a1
            df = 0.5*(gx + gy) - sqrt(2.0*gx*gy*a);
        } else if (a < (1.0-a1)) {
            // a1 <= a <= 1-a1
            df = (0.5-a)*gx;
        } else {
            // 1-a1 < a <= 1
            df = -0.5*(gx + gy) + sqrt(2.0*gx*gy*(1.0-a));
        }
    }
    return df;
}
double distaa3(double *img, double *gximg, double *gyimg, int w, int c, int xc, int yc, int xi, int yi)
{
    double di, df, dx, dy, gx, gy, a;
    int closest;
    closest = c-xc-yc*w; // Index to the edge pixel pointed to from c
    a = img[closest];    // Grayscale value at the edge pixel
    gx = gximg[closest]; // X gradient component at the edge pixel
    gy = gyimg[closest]; // Y gradient component at the edge pixel
    if(a > 1.0) a = 1.0;
    if(a < 0.0) a = 0.0; // Clip grayscale values outside the range [0,1]
    if(a == 0.0) return 1000000.0; // Not an object pixel, return "very far" ("don't know yet")
    dx = (double)xi;
    dy = (double)yi;
    di = sqrt(dx*dx + dy*dy); // Length of integer vector, like a traditional EDT
    if(di==0) {
        // Use local gradient only at edges
        // Estimate based on local gradient only
        df = edgedf(gx, gy, a);
    } else {
        // Estimate gradient based on direction to edge (accurate for large di)
        df = edgedf(dx, dy, a);
    }
    return di + df; // Same metric as edtaa2, except at edges (where di=0)
}
// Shorthand macro: add ubiquitous parameters dist, gx, gy, img and w and call distaa3()
#define DISTAA(c,xc,yc,xi,yi) (distaa3(img, gx, gy, w, c, xc, yc, xi, yi))
void edtaa3(double *img, double *gx, double *gy, int w, int h, short *distx, short *disty, double *dist)
{
    int x, y, i, c;
    int offset_u, offset_ur, offset_r, offset_rd,
    offset_d, offset_dl, offset_l, offset_lu;
    double olddist, newdist;
    int cdistx, cdisty, newdistx, newdisty;
    int changed;
    double epsilon = 1e-3;
    /* Initialize index offsets for the current image width */
    offset_u = -w;
    offset_ur = -w+1;
    offset_r = 1;
    offset_rd = w+1;
    offset_d = w;
    offset_dl = w-1;
    offset_l = -1;
    offset_lu = -w-1;
    /* Initialize the distance images */
    for(i=0; i<w*h; i++) {
        distx[i] = 0; // At first, all pixels point to
        disty[i] = 0; // themselves as the closest known.
        if(img[i] <= 0.0)
        {
            dist[i]= 1000000.0; // Big value, means "not set yet"
        }
        else if (img[i]<1.0) {
            dist[i] = edgedf(gx[i], gy[i], img[i]); // Gradient-assisted estimate
        }
        else {
            dist[i]= 0.0; // Inside the object
        }
    }
    /* Perform the transformation */
    do
    {
        changed = 0;
        /* Scan rows, except first row */
        for(y=1; y<h; y++)
        {
            /* move index to leftmost pixel of current row */
            i = y*w;
            /* scan right, propagate distances from above & left */
            /* Leftmost pixel is special, has no left neighbors */
            olddist = dist[i];
            if(olddist > 0) // If non-zero distance or not set yet
            {
                c = i + offset_u; // Index of candidate for testing
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx;
                newdisty = cdisty+1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    olddist=newdist;
                    changed = 1;
                }
                c = i+offset_ur;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx-1;
                newdisty = cdisty+1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    changed = 1;
                }
            }
            i++;
            /* Middle pixels have all neighbors */
            for(x=1; x<w-1; x++, i++)
            {
                olddist = dist[i];
                if(olddist <= 0) continue; // No need to update further
                c = i+offset_l;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx+1;
                newdisty = cdisty;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    olddist=newdist;
                    changed = 1;
                }
                c = i+offset_lu;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx+1;
                newdisty = cdisty+1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    olddist=newdist;
                    changed = 1;
                }
                c = i+offset_u;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx;
                newdisty = cdisty+1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    olddist=newdist;
                    changed = 1;
                }
                c = i+offset_ur;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx-1;
                newdisty = cdisty+1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    changed = 1;
                }
            }
            /* Rightmost pixel of row is special, has no right neighbors */
            olddist = dist[i];
            if(olddist > 0) // If not already zero distance
            {
                c = i+offset_l;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx+1;
                newdisty = cdisty;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    olddist=newdist;
                    changed = 1;
                }
                c = i+offset_lu;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx+1;
                newdisty = cdisty+1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    olddist=newdist;
                    changed = 1;
                }
                c = i+offset_u;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx;
                newdisty = cdisty+1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    changed = 1;
                }
            }
            /* Move index to second rightmost pixel of current row. */
            /* Rightmost pixel is skipped, it has no right neighbor. */
            i = y*w + w-2;
            /* scan left, propagate distance from right */
            for(x=w-2; x>=0; x--, i--)
            {
                olddist = dist[i];
                if(olddist <= 0) continue; // Already zero distance
                c = i+offset_r;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx-1;
                newdisty = cdisty;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    changed = 1;
                }
            }
        }
        /* Scan rows in reverse order, except last row */
        for(y=h-2; y>=0; y--)
        {
            /* move index to rightmost pixel of current row */
            i = y*w + w-1;
            /* Scan left, propagate distances from below & right */
            /* Rightmost pixel is special, has no right neighbors */
            olddist = dist[i];
            if(olddist > 0) // If not already zero distance
            {
                c = i+offset_d;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx;
                newdisty = cdisty-1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    olddist=newdist;
                    changed = 1;
                }
                c = i+offset_dl;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx+1;
                newdisty = cdisty-1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    changed = 1;
                }
            }
            i--;
            /* Middle pixels have all neighbors */
            for(x=w-2; x>0; x--, i--)
            {
                olddist = dist[i];
                if(olddist <= 0) continue; // Already zero distance
                c = i+offset_r;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx-1;
                newdisty = cdisty;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    olddist=newdist;
                    changed = 1;
                }
                c = i+offset_rd;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx-1;
                newdisty = cdisty-1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    olddist=newdist;
                    changed = 1;
                }
                c = i+offset_d;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx;
                newdisty = cdisty-1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    olddist=newdist;
                    changed = 1;
                }
                c = i+offset_dl;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx+1;
                newdisty = cdisty-1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    changed = 1;
                }
            }
            /* Leftmost pixel is special, has no left neighbors */
            olddist = dist[i];
            if(olddist > 0) // If not already zero distance
            {
                c = i+offset_r;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx-1;
                newdisty = cdisty;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    olddist=newdist;
                    changed = 1;
                }
                c = i+offset_rd;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx-1;
                newdisty = cdisty-1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    olddist=newdist;
                    changed = 1;
                }
                c = i+offset_d;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx;
                newdisty = cdisty-1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    changed = 1;
                }
            }
            /* Move index to second leftmost pixel of current row. */
            /* Leftmost pixel is skipped, it has no left neighbor. */
            i = y*w + 1;
            for(x=1; x<w; x++, i++)
            {
                /* scan right, propagate distance from left */
                olddist = dist[i];
                if(olddist <= 0) continue; // Already zero distance
                c = i+offset_l;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx+1;
                newdisty = cdisty;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    changed = 1;
                }
            }
        }
    }
    while(changed); // Sweep until no more updates are made
    /* The transformation is completed. */
}
#ifndef fontkey_weak_font_hash_function
#define fontkey_weak_font_hash_function
#if true
KHASH_INIT_FUNCTION_DEREF(fontkey_weak_font_hash_type, sjs_fontkey, sjs_font*, 1, sjf_fontkey_hash, sjf_fontkey_isequal)
#else
KHASH_INIT_FUNCTION(fontkey_weak_font_hash_type, sjs_fontkey, sjs_font*, 1, sjf_fontkey_hash, sjf_fontkey_isequal)
#endif
#endif
#ifndef fontkey_weak_font_hash_function
#define fontkey_weak_font_hash_function
#if true
KHASH_INIT_FUNCTION_DEREF(fontkey_weak_font_hash_type, sjs_fontkey, sjs_font*, 1, sjf_fontkey_hash, sjf_fontkey_isequal)
#else
KHASH_INIT_FUNCTION(fontkey_weak_font_hash_type, sjs_fontkey, sjs_font*, 1, sjf_fontkey_hash, sjf_fontkey_isequal)
#endif
#endif
KHASH_INIT_TYPEDEF(glid_hash_type, GLuint, int)
KHASH_INIT_FUNCTION(glid_hash_type, GLuint, int, 1, glid_gethash, glid_isequal)
khash_t(glid_hash_type)* glid_hash;
void glid_gethash(GLuint id, uint32_t* result) {
    *result = kh_int_hash_func(id);
}
void glid_isequal(GLuint id1, GLuint id2, bool* result) {
    *result = (id1 == id2);
}
void glid_init() {
    glid_hash = kh_init(glid_hash_type);
}
void glid_retain(GLuint id) {
    khiter_t k = kh_get(glid_hash_type, glid_hash, id);
    if (k == kh_end(glid_hash)) {
        int ret;
        khiter_t k = kh_put(glid_hash_type, glid_hash, id, &ret);
        if (!ret) kh_del(glid_hash_type, glid_hash, k);
        kh_value(glid_hash, k) = 1;
    }
    else {
        kh_value(glid_hash, k)++;
    }
}
bool glid_release(GLuint id) {
    khiter_t k = kh_get(glid_hash_type, glid_hash, id);
    if (k != kh_end(glid_hash)) {
        kh_value(glid_hash, k)--;
        if (kh_value(glid_hash, k) == 0) {
            kh_del(glid_hash_type, glid_hash, k);
        }
        return false;
    }
    return true;
}
char *repl_str(const char *str, const char *from, const char *to) {
    /* Adjust each of the below values to suit your needs. */
    /* Increment positions cache size initially by this number. */
    size_t cache_sz_inc = 16;
    /* Thereafter, each time capacity needs to be increased,
    * multiply the increment by this factor. */
    const size_t cache_sz_inc_factor = 3;
    /* But never increment capacity by more than this number. */
    const size_t cache_sz_inc_max = 1048576;
    char *pret, *ret = NULL;
    const char *pstr2, *pstr = str;
    size_t i, count = 0;
    #if (__STDC_VERSION__ >= 199901L)
    uintptr_t *pos_cache_tmp, *pos_cache = NULL;
    #else
    ptrdiff_t *pos_cache_tmp, *pos_cache = NULL;
    #endif
    size_t cache_sz = 0;
    size_t cpylen, orglen, retlen, tolen = 0, fromlen = strlen(from);
    /* Find all matches and cache their positions. */
    while ((pstr2 = strstr(pstr, from)) != NULL) {
        count++;
        /* Increase the cache size when necessary. */
        if (cache_sz < count) {
            cache_sz += cache_sz_inc;
            pos_cache_tmp = realloc(pos_cache, sizeof(*pos_cache) * cache_sz);
            if (pos_cache_tmp == NULL) {
                goto end_repl_str;
            } else pos_cache = pos_cache_tmp;
            cache_sz_inc *= cache_sz_inc_factor;
            if (cache_sz_inc > cache_sz_inc_max) {
                cache_sz_inc = cache_sz_inc_max;
            }
        }
        pos_cache[count-1] = pstr2 - str;
        pstr = pstr2 + fromlen;
    }
    orglen = pstr - str + strlen(pstr);
    /* Allocate memory for the post-replacement string. */
    if (count > 0) {
        tolen = strlen(to);
        retlen = orglen + (tolen - fromlen) * count;
    } else  retlen = orglen;
    ret = malloc(retlen + 1);
    if (ret == NULL) {
        goto end_repl_str;
    }
    if (count == 0) {
        /* If no matches, then just duplicate the string. */
        strcpy(ret, str);
    } else {
        /* Otherwise, duplicate the string whilst performing
        * the replacements using the position cache. */
        pret = ret;
        memcpy(pret, str, pos_cache[0]);
        pret += pos_cache[0];
        for (i = 0; i < count; i++) {
            memcpy(pret, to, tolen);
            pret += tolen;
            pstr = str + pos_cache[i] + fromlen;
            cpylen = (i == count-1 ? orglen : pos_cache[i+1]) - pos_cache[i] - fromlen;
            memcpy(pret, pstr, cpylen);
            pret += cpylen;
        }
        ret[retlen] = '\0';
    }
    end_repl_str:
    /* Free the cache and return the post-replacement string,
    * which will be NULL in the event of an error. */
    free(pos_cache);
    return ret;
}
// ------------------------------------------------------------ shader_read ---
char *
shader_read( const char *filename )
{
    FILE * file;
    char * buffer;
    size_t size;
    #ifdef WIN32
    errno_t err;
    if( (err  = fopen_s( &file, filename, "rb" )) !=0 ) {
        #else
        file = fopen( filename, "rb" );
        if( !file ) {
            #endif
            fprintf( stderr, "Unable to open file \"%s\".\n", filename );
            return 0;
        }
        fseek( file, 0, SEEK_END );
        size = ftell( file );
        fseek(file, 0, SEEK_SET );
        buffer = (char *) malloc( (size+1) * sizeof( char *) );
        fread( buffer, sizeof(char), size, file );
        buffer[size] = 0;
        fclose( file );
        #ifdef __APPLE__
        char* prev = buffer;
        buffer = repl_str(buffer, "mediump", "");
        free(prev);
        #endif
        return buffer;
    }
    // --------------------------------------------------------- shader_compile ---
    GLuint
    shader_compile( const char* source,
    const GLenum type )
    {
        GLint compile_status;
        GLuint handle = glCreateShader( type );
        glShaderSource( handle, 1, &source, 0 );
        glCompileShader( handle );
        glGetShaderiv( handle, GL_COMPILE_STATUS, &compile_status );
        if( compile_status == GL_FALSE )
        {
            GLchar messages[256];
            glGetShaderInfoLog( handle, sizeof(messages), 0, &messages[0] );
            halt("%s: %s\n", source, messages);
        }
        return handle;
    }
    // ------------------------------------------------------------ shader_load ---
    GLuint
    shader_load( const char * vert_filename,
    const char * frag_filename )
    {
        GLuint handle = glCreateProgram( );
        GLint link_status;
        if( vert_filename && strlen( vert_filename ) )
        {
            char *vert_source = shader_read( vert_filename );
            GLuint vert_shader = shader_compile( vert_source, GL_VERTEX_SHADER);
            glAttachShader( handle, vert_shader);
            glDeleteShader( vert_shader );
            free( vert_source );
        }
        if( frag_filename && strlen( frag_filename ) )
        {
            char *frag_source = shader_read( frag_filename );
            GLuint frag_shader = shader_compile( frag_source, GL_FRAGMENT_SHADER);
            glAttachShader( handle, frag_shader);
            glDeleteShader( frag_shader );
            free( frag_source );
        }
        glLinkProgram( handle );
        glGetProgramiv( handle, GL_LINK_STATUS, &link_status );
        if (link_status == GL_FALSE)
        {
            GLchar messages[256];
            glGetProgramInfoLog( handle, sizeof(messages), 0, &messages[0] );
            halt("%s\n", messages );
        }
        return handle;
    }
    void add_text(vertex_buffer_t * buffer, texture_font_t * font, char *text, int textlen, vec4 * color, vec2 * pen) {
        pen->y += (float)(int)font->ascender;
        size_t i;
        float r = color->red, g = color->green, b = color->blue, a = color->alpha;
        for (i = 0; i < (size_t)textlen; ++i) {
            texture_glyph_t *glyph = texture_font_get_glyph( font, text + i );
            if (glyph != NULL) {
                float kerning = 0.0f;
                if( i > 0) {
                    kerning = texture_glyph_get_kerning( glyph, text + i - 1 );
                }
                pen->x += kerning;
                float x0 = (float)(int)( pen->x + glyph->offset_x );
                float y0 = (float)(int)( pen->y + glyph->height - glyph->offset_y );
                float x1 = (float)(int)( x0 + glyph->width );
                float y1 = (float)(int)( y0 - glyph->height );
                float s0 = glyph->s0;
                float t0 = glyph->t0;
                float s1 = glyph->s1;
                float t1 = glyph->t1;
                GLuint index = (GLuint)buffer->vertices->size;
                GLuint indices[] = { //
                index, index+1, index+2,
                index, index+2, index+3 };
                vertex3_texture2_color3_t vertices[] = { //
                { x0, y1, 0.0f,  s0,t0,  r,g,b,a },
                { x0, y0, 0.0f,  s0,t1,  r,g,b,a },
                { x1, y0, 0.0f,  s1,t1,  r,g,b,a },
                { x1, y1, 0.0f,  s1,t0,  r,g,b,a } };
                vertex_buffer_push_back_indices( buffer, indices, 6 );
                vertex_buffer_push_back_vertices( buffer, vertices, 4 );
                pen->x += glyph->advance_x;
            }
        }
    }   
    vec2 get_text_size(texture_font_t * font, char *text) {
        vec2 size = {{ 0, font->height }};
        size_t i;
        for( i = 0; i < strlen(text); ++i ) {
            texture_glyph_t *glyph = texture_font_get_glyph(font, text + i);
            if (glyph != NULL) {
                float kerning = 0.0f;
                if( i > 0) {
                    kerning = texture_glyph_get_kerning(glyph, text + i - 1);
                }
                size.x += kerning;
                size.x += glyph->advance_x;
            }
        }
        return size;
    }   
    GLuint png_texture_load(const char * file_name, int * width, int * height)
    {
        // This function was originally written by David Grayson for
        // https://github.com/DavidEGrayson/ahrs-visualizer
        png_byte header[8];
        FILE *fp = fopen(file_name, "rb");
        if (fp == 0)
        {
            perror(file_name);
            return 0;
        }
        // read the header
        fread(header, 1, 8, fp);
        if (png_sig_cmp(header, 0, 8))
        {
            fprintf(stderr, "error: %s is not a PNG.\n", file_name);
            fclose(fp);
            return 0;
        }
        png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (!png_ptr)
        {
            fprintf(stderr, "error: png_create_read_struct returned 0.\n");
            fclose(fp);
            return 0;
        }
        // create png info struct
        png_infop info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr)
        {
            fprintf(stderr, "error: png_create_info_struct returned 0.\n");
            png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
            fclose(fp);
            return 0;
        }
        // create png info struct
        png_infop end_info = png_create_info_struct(png_ptr);
        if (!end_info)
        {
            fprintf(stderr, "error: png_create_info_struct returned 0.\n");
            png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
            fclose(fp);
            return 0;
        }
        // the code in this if statement gets called if libpng encounters an error
        if (setjmp(png_jmpbuf(png_ptr))) {
            fprintf(stderr, "error from libpng\n");
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
            fclose(fp);
            return 0;
        }
        // init png reading
        png_init_io(png_ptr, fp);
        // let libpng know you already read the first 8 bytes
        png_set_sig_bytes(png_ptr, 8);
        // read all the info up to the image data
        png_read_info(png_ptr, info_ptr);
        // variables to pass to get info
        int bit_depth, color_type;
        png_uint_32 temp_width, temp_height;
        // get info about png
        png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth, &color_type,
        NULL, NULL, NULL);
        if (width){ *width = temp_width; }
        if (height){ *height = temp_height; }
        //printf("%s: %lux%lu %d\n", file_name, temp_width, temp_height, color_type);
        if (bit_depth != 8)
        {
            fprintf(stderr, "%s: Unsupported bit depth %d.  Must be 8.\n", file_name, bit_depth);
            return 0;
        }
        GLint format;
        switch(color_type)
        {
            case PNG_COLOR_TYPE_RGB:
            format = GL_RGB;
            break;
            case PNG_COLOR_TYPE_RGB_ALPHA:
            format = GL_RGBA;
            break;
            default:
            fprintf(stderr, "%s: Unknown libpng color type %d.\n", file_name, color_type);
            return 0;
        }
        // Update the png info struct.
        png_read_update_info(png_ptr, info_ptr);
        // Row size in bytes.
        int rowbytes = (int)png_get_rowbytes(png_ptr, info_ptr);
        // glTexImage2d requires rows to be 4-byte aligned
        rowbytes += 3 - ((rowbytes-1) % 4);
        // Allocate the image_data as a big block, to be given to opengl
        png_byte * image_data = (png_byte *)malloc(rowbytes * temp_height * sizeof(png_byte)+15);
        if (image_data == NULL)
        {
            fprintf(stderr, "error: could not allocate memory for PNG image data\n");
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
            fclose(fp);
            return 0;
        }
        // row_pointers is for pointing to image_data for reading the png with libpng
        png_byte ** row_pointers = (png_byte **)malloc(temp_height * sizeof(png_byte *));
        if (row_pointers == NULL)
        {
            fprintf(stderr, "error: could not allocate memory for PNG row pointers\n");
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
            free(image_data);
            fclose(fp);
            return 0;
        }
        // set the individual row_pointers to point at the correct offsets of image_data
        for (unsigned int i = 0; i < temp_height; i++)
        {
            row_pointers[temp_height - 1 - i] = image_data + i * rowbytes;
        }
        // read the png into image_data through row_pointers
        png_read_image(png_ptr, row_pointers);
        // Generate the OpenGL texture object
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexImage2D(GL_TEXTURE_2D, 0, format, temp_width, temp_height, 0, format, GL_UNSIGNED_BYTE, image_data);
        // clean up
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        free(image_data);
        free(row_pointers);
        fclose(fp);
        return texture;
    }
    // ------------------------------------------------------ texture_atlas_new ---
    texture_atlas_t *
    texture_atlas_new( const size_t width,
    const size_t height,
    const size_t depth )
    {
        texture_atlas_t *self = (texture_atlas_t *) malloc( sizeof(texture_atlas_t) );
        // We want a one pixel border around the whole atlas to avoid any artefact when
        // sampling texture
        ivec3 node = {{1,1, (int)width-2}};
        assert( (depth == 1) || (depth == 3) || (depth == 4) );
        if( self == NULL)
        {
            halt("line %d: No more memory for allocating data\n", __LINE__ );
        }
        self->nodes = vector_new( sizeof(ivec3) );
        self->used = 0;
        self->width = width;
        self->height = height;
        self->depth = depth;
        self->id = 0;
        vector_push_back( self->nodes, &node );
        self->data = (unsigned char *)
        calloc( width*height*depth, sizeof(unsigned char) );
        if( self->data == NULL)
        {
            halt("line %d: No more memory for allocating data\n", __LINE__ );
        }
        return self;
    }
    // --------------------------------------------------- texture_atlas_delete ---
    void
    texture_atlas_delete( texture_atlas_t *self )
    {
        assert( self );
        vector_delete( self->nodes );
        if( self->data )
        {
            free( self->data );
        }
        free( self );
    }
    // ----------------------------------------------- texture_atlas_set_region ---
    void
    texture_atlas_set_region( texture_atlas_t * self,
    const size_t x,
    const size_t y,
    const size_t width,
    const size_t height,
    const unsigned char * data,
    const size_t stride )
    {
        size_t i;
        size_t depth;
        size_t charsize;
        assert( self );
        assert( x > 0);
        assert( y > 0);
        assert( x < (self->width-1));
        assert( (x + width) <= (self->width-1));
        assert( y < (self->height-1));
        assert( (y + height) <= (self->height-1));
        //prevent copying data from undefined position 
        //and prevent memcpy's undefined behavior when count is zero
        assert(height == 0 || (data != NULL && width > 0));
        depth = self->depth;
        charsize = sizeof(char);
        for( i=0; i<height; ++i )
        {
            memcpy( self->data+((y+i)*self->width + x ) * charsize * depth,
            data + (i*stride) * charsize, width * charsize * depth  );
        }
    }
    // ------------------------------------------------------ texture_atlas_fit ---
    int
    texture_atlas_fit( texture_atlas_t * self,
    const size_t index,
    const size_t width,
    const size_t height )
    {
        ivec3 *node;
        int x, y, width_left;
        size_t i;
        assert( self );
        node = (ivec3 *) (vector_get( self->nodes, index ));
        x = node->x;
        y = node->y;
        width_left = (int)width;
        i = index;
        if ( (x + width) > (self->width-1) )
        {
            return -1;
        }
        y = node->y;
        while( width_left > 0 )
        {
            node = (ivec3 *) (vector_get( self->nodes, i ));
            if( node->y > y )
            {
                y = node->y;
            }
            if( (y + height) > (self->height-1) )
            {
                return -1;
            }
            width_left -= node->z;
            ++i;
        }
        return y;
    }
    // ---------------------------------------------------- texture_atlas_merge ---
    void
    texture_atlas_merge( texture_atlas_t * self )
    {
        ivec3 *node, *next;
        size_t i;
        assert( self );
        for( i=0; i< self->nodes->size-1; ++i )
        {
            node = (ivec3 *) (vector_get( self->nodes, i ));
            next = (ivec3 *) (vector_get( self->nodes, i+1 ));
            if( node->y == next->y )
            {
                node->z += next->z;
                vector_erase( self->nodes, i+1 );
                --i;
            }
        }
    }
    // ----------------------------------------------- texture_atlas_get_region ---
    ivec4
    texture_atlas_get_region( texture_atlas_t * self,
    const size_t width,
    const size_t height )
    {
        int y, best_index;
        size_t best_height, best_width;
        ivec3 *node, *prev;
        ivec4 region = {{0,0,(int)width,(int)height}};
        size_t i;
        assert( self );
        best_height = UINT_MAX;
        best_index  = -1;
        best_width = UINT_MAX;
        for( i=0; i<self->nodes->size; ++i )
        {
            y = texture_atlas_fit( self, i, width, height );
            if( y >= 0 )
            {
                node = (ivec3 *) vector_get( self->nodes, i );
                if( ( (y + height) < best_height ) ||
                ( ((y + height) == best_height) && (node->z > 0 && (size_t)node->z < best_width)) )
                {
                    best_height = y + height;
                    best_index = (int)i;
                    best_width = node->z;
                    region.x = node->x;
                    region.y = y;
                }
            }
        }
        if( best_index == -1 )
        {
            region.x = -1;
            region.y = -1;
            region.width = 0;
            region.height = 0;
            return region;
        }
        node = (ivec3 *) malloc( sizeof(ivec3) );
        if( node == NULL)
        {
            halt("line %d: No more memory for allocating data\n", __LINE__ );
        }
        node->x = region.x;
        node->y = (int)(region.y + height);
        node->z = (int)width;
        vector_insert( self->nodes, best_index, node );
        free( node );
        for(i = best_index+1; i < self->nodes->size; ++i)
        {
            node = (ivec3 *) vector_get( self->nodes, i );
            prev = (ivec3 *) vector_get( self->nodes, i-1 );
            if (node->x < (prev->x + prev->z) )
            {
                int shrink = prev->x + prev->z - node->x;
                node->x += shrink;
                node->z -= shrink;
                if (node->z <= 0)
                {
                    vector_erase( self->nodes, i );
                    --i;
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
        texture_atlas_merge( self );
        self->used += width * height;
        return region;
    }
    // ---------------------------------------------------- texture_atlas_clear ---
    void
    texture_atlas_clear( texture_atlas_t * self )
    {
        ivec3 node = {{1,1,1}};
        assert( self );
        assert( self->data );
        vector_clear( self->nodes );
        self->used = 0;
        // We want a one pixel border around the whole atlas to avoid any artefact when
        // sampling texture
        node.z = (int)(self->width-2);
        vector_push_back( self->nodes, &node );
        memset( self->data, 0, self->width*self->height*self->depth );
    }
    #define HRES  64
    #define HRESf 64.f
    #define DPI   72
    // ------------------------------------------------- texture_font_load_face ---
    static int
    texture_font_load_face(texture_font_t *self, float size,
    FT_Library *library, FT_Face *face)
    {
        FT_Error error;
        FT_Matrix matrix = { //
        (int)((1.0/HRES) * 0x10000L),
        (int)((0.0)      * 0x10000L),
        (int)((0.0)      * 0x10000L),
        (int)((1.0)      * 0x10000L)};
        assert(library);
        assert(size);
        /* Initialize library */
        error = FT_Init_FreeType(library);
        if(error) {
            fprintf(stderr, "FT_Error (0x%02x) : %s\n",
            FT_Errors[error].code, FT_Errors[error].message);
            goto cleanup;
        }
        /* Load face */
        switch (self->location) {
            case TEXTURE_FONT_FILE:
            error = FT_New_Face(*library, self->filename, 0, face);
            break;
            case TEXTURE_FONT_MEMORY:
            error = FT_New_Memory_Face(*library,
            self->memory.base, self->memory.size, 0, face);
            break;
        }
        if(error) {
            fprintf(stderr, "FT_Error (line %d, code 0x%02x) : %s\n",
            __LINE__, FT_Errors[error].code, FT_Errors[error].message);
            goto cleanup_library;
        }
        /* Select charmap */
        error = FT_Select_Charmap(*face, FT_ENCODING_UNICODE);
        if(error) {
            fprintf(stderr, "FT_Error (line %d, code 0x%02x) : %s\n",
            __LINE__, FT_Errors[error].code, FT_Errors[error].message);
            goto cleanup_face;
        }
        /* Set char size */
        error = FT_Set_Char_Size(*face, (int)(size * HRES), 0, DPI * HRES, DPI);
        if(error) {
            fprintf(stderr, "FT_Error (line %d, code 0x%02x) : %s\n",
            __LINE__, FT_Errors[error].code, FT_Errors[error].message);
            goto cleanup_face;
        }
        /* Set transform matrix */
        FT_Set_Transform(*face, &matrix, NULL);
        return 1;
        cleanup_face:
        FT_Done_Face( *face );
        cleanup_library:
        FT_Done_FreeType( *library );
        cleanup:
        return 0;
    }
    // ------------------------------------------------------ texture_glyph_new ---
    texture_glyph_t *
    texture_glyph_new(void)
    {
        texture_glyph_t *self = (texture_glyph_t *) malloc( sizeof(texture_glyph_t) );
        if(self == NULL) {
            fprintf( stderr,
            "line %d: No more memory for allocating data\n", __LINE__);
            return NULL;
        }
        self->codepoint  = -1;
        self->width     = 0;
        self->height    = 0;
        self->rendermode = RENDER_NORMAL;
        self->outline_thickness = 0.0;
        self->offset_x  = 0;
        self->offset_y  = 0;
        self->advance_x = 0.0;
        self->advance_y = 0.0;
        self->s0        = 0.0;
        self->t0        = 0.0;
        self->s1        = 0.0;
        self->t1        = 0.0;
        self->kerning   = vector_new( sizeof(kerning_t) );
        return self;
    }
    // --------------------------------------------------- texture_glyph_delete ---
    void
    texture_glyph_delete( texture_glyph_t *self )
    {
        assert( self );
        vector_delete( self->kerning );
        free( self );
    }
    // ---------------------------------------------- texture_glyph_get_kerning ---
    float
    texture_glyph_get_kerning( const texture_glyph_t * self,
    const char * codepoint )
    {
        size_t i;
        uint32_t ucodepoint = utf8_to_utf32( codepoint );
        assert( self );
        for( i=0; i<vector_size(self->kerning); ++i )
        {
            kerning_t * kerning = (kerning_t *) vector_get( self->kerning, i );
            if( kerning->codepoint == ucodepoint )
            {
                return kerning->kerning;
            }
        }
        return 0;
    }
    // ------------------------------------------ texture_font_generate_kerning ---
    void
    texture_font_generate_kerning( texture_font_t *self,
    FT_Library *library, FT_Face *face )
    {
        size_t i, j;
        FT_UInt glyph_index, prev_index;
        texture_glyph_t *glyph, *prev_glyph;
        FT_Vector kerning;
        assert( self );
        /* For each glyph couple combination, check if kerning is necessary */
        /* Starts at index 1 since 0 is for the special backgroudn glyph */
        for( i=1; i<self->glyphs->size; ++i )
        {
            glyph = *(texture_glyph_t **) vector_get( self->glyphs, i );
            glyph_index = FT_Get_Char_Index( *face, glyph->codepoint );
            vector_clear( glyph->kerning );
            for( j=1; j<self->glyphs->size; ++j )
            {
                prev_glyph = *(texture_glyph_t **) vector_get( self->glyphs, j );
                prev_index = FT_Get_Char_Index( *face, prev_glyph->codepoint );
                FT_Get_Kerning( *face, prev_index, glyph_index, FT_KERNING_UNFITTED, &kerning );
                // printf("%c(%d)-%c(%d): %ld\n",
                //       prev_glyph->codepoint, prev_glyph->codepoint,
                //       glyph_index, glyph_index, kerning.x);
                if( kerning.x )
                {
                    kerning_t k = {prev_glyph->codepoint, kerning.x / (float)(HRESf*HRESf)};
                    vector_push_back( glyph->kerning, &k );
                }
            }
        }
    }
    // ------------------------------------------------------ texture_font_init ---
    static int
    texture_font_init(texture_font_t *self)
    {
        FT_Library library;
        FT_Face face;
        FT_Size_Metrics metrics;
        assert(self->atlas);
        assert(self->size > 0);
        assert((self->location == TEXTURE_FONT_FILE && self->filename)
        || (self->location == TEXTURE_FONT_MEMORY
        && self->memory.base && self->memory.size));
        self->glyphs = vector_new(sizeof(texture_glyph_t *));
        self->height = 0;
        self->ascender = 0;
        self->descender = 0;
        self->rendermode = RENDER_NORMAL;
        self->outline_thickness = 0.0;
        self->hinting = 1;
        self->kerning = 1;
        self->filtering = 1;
        // FT_LCD_FILTER_LIGHT   is (0x00, 0x55, 0x56, 0x55, 0x00)
        // FT_LCD_FILTER_DEFAULT is (0x10, 0x40, 0x70, 0x40, 0x10)
        self->lcd_weights[0] = 0x10;
        self->lcd_weights[1] = 0x40;
        self->lcd_weights[2] = 0x70;
        self->lcd_weights[3] = 0x40;
        self->lcd_weights[4] = 0x10;
        if (!texture_font_load_face(self, self->size * 100.f, &library, &face))
        return -1;
        self->underline_position = face->underline_position / (float)(HRESf*HRESf) * self->size;
        self->underline_position = roundf( self->underline_position );
        if( self->underline_position > -2 )
        {
            self->underline_position = -2.0;
        }
        self->underline_thickness = face->underline_thickness / (float)(HRESf*HRESf) * self->size;
        self->underline_thickness = roundf( self->underline_thickness );
        if( self->underline_thickness < 1 )
        {
            self->underline_thickness = 1.0;
        }
        metrics = face->size->metrics;
        self->ascender = (metrics.ascender >> 6) / 100.0f;
        self->descender = (metrics.descender >> 6) / 100.0f;
        self->height = (metrics.height >> 6) / 100.0f;
        self->linegap = self->height - self->ascender + self->descender;
        FT_Done_Face( face );
        FT_Done_FreeType( library );
        /* NULL is a special glyph */
        texture_font_get_glyph( self, NULL );
        return 0;
    }
    // --------------------------------------------- texture_font_new_from_file ---
    texture_font_t *
    texture_font_new_from_file(texture_atlas_t *atlas, const float pt_size,
    const char *filename)
    {
        texture_font_t *self;
        assert(filename);
        self = calloc(1, sizeof(*self));
        if (!self) {
            fprintf(stderr,
            "line %d: No more memory for allocating data\n", __LINE__);
            return NULL;
        }
        self->atlas = atlas;
        self->size  = pt_size;
        self->location = TEXTURE_FONT_FILE;
        self->filename = strdup(filename);
        if (texture_font_init(self)) {
            texture_font_delete(self);
            return NULL;
        }
        return self;
    }
    // ------------------------------------------- texture_font_new_from_memory ---
    texture_font_t *
    texture_font_new_from_memory(texture_atlas_t *atlas, float pt_size,
    const void *memory_base, size_t memory_size)
    {
        texture_font_t *self;
        assert(memory_base);
        assert(memory_size);
        self = calloc(1, sizeof(*self));
        if (!self) {
            fprintf(stderr,
            "line %d: No more memory for allocating data\n", __LINE__);
            return NULL;
        }
        self->atlas = atlas;
        self->size  = pt_size;
        self->location = TEXTURE_FONT_MEMORY;
        self->memory.base = memory_base;
        self->memory.size = memory_size;
        if (texture_font_init(self)) {
            texture_font_delete(self);
            return NULL;
        }
        return self;
    }
    // ---------------------------------------------------- texture_font_delete ---
    void
    texture_font_delete( texture_font_t *self )
    {
        size_t i;
        texture_glyph_t *glyph;
        assert( self );
        if(self->location == TEXTURE_FONT_FILE && self->filename)
        free( self->filename );
        for( i=0; i<vector_size( self->glyphs ); ++i)
        {
            glyph = *(texture_glyph_t **) vector_get( self->glyphs, i );
            texture_glyph_delete( glyph);
        }
        vector_delete( self->glyphs );
        free( self );
    }
    texture_glyph_t *
    texture_font_find_glyph( texture_font_t * self,
    const char * codepoint )
    {
        size_t i;
        texture_glyph_t *glyph;
        uint32_t ucodepoint = utf8_to_utf32( codepoint );
        for( i = 0; i < self->glyphs->size; ++i )
        {
            glyph = *(texture_glyph_t **) vector_get( self->glyphs, i );
            // If codepoint is -1, we don't care about outline type or thickness
            if( (glyph->codepoint == ucodepoint) &&
            ((ucodepoint == -1) ||
            ((glyph->rendermode == self->rendermode) &&
            (glyph->outline_thickness == self->outline_thickness)) ))
            {
                return glyph;
            }
        }
        return NULL;
    }
    // ------------------------------------------------ texture_font_load_glyph ---
    int
    texture_font_load_glyph( texture_font_t * self,
    const char * codepoint )
    {
        size_t i, x, y;
        FT_Library library;
        FT_Error error;
        FT_Face face;
        FT_Glyph ft_glyph = { 0 };
        FT_GlyphSlot slot;
        FT_Bitmap ft_bitmap;
        FT_UInt glyph_index;
        texture_glyph_t *glyph;
        FT_Int32 flags = 0;
        int ft_glyph_top = 0;
        int ft_glyph_left = 0;
        ivec4 region;
        if (!texture_font_load_face(self, self->size, &library, &face))
        return 0;
        /* Check if codepoint has been already loaded */
        if (texture_font_find_glyph(self, codepoint)) {
            FT_Done_Face(face);
            FT_Done_FreeType(library);
            return 1;
        }
        /* codepoint NULL is special : it is used for line drawing (overline,
        * underline, strikethrough) and background.
        */
        if( !codepoint )
        {
            ivec4 region = texture_atlas_get_region( self->atlas, 5, 5 );
            texture_glyph_t * glyph = texture_glyph_new( );
            static unsigned char data[4*4*3] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
            if ( region.x < 0 )
            {
                fprintf( stderr, "Texture atlas is full (line %d)\n",  __LINE__ );
                FT_Done_Face( face );
                FT_Done_FreeType( library );
                return 0;
            }
            texture_atlas_set_region( self->atlas, region.x, region.y, 4, 4, data, 0 );
            glyph->codepoint = -1;
            glyph->s0 = (region.x+2)/(float)self->atlas->width;
            glyph->t0 = (region.y+2)/(float)self->atlas->height;
            glyph->s1 = (region.x+3)/(float)self->atlas->width;
            glyph->t1 = (region.y+3)/(float)self->atlas->height;
            vector_push_back( self->glyphs, &glyph );
            FT_Done_Face(face);
            FT_Done_FreeType(library);
            return 1;
        }
        flags = 0;
        ft_glyph_top = 0;
        ft_glyph_left = 0;
        glyph_index = FT_Get_Char_Index( face, (FT_ULong)utf8_to_utf32( codepoint ) );
        // WARNING: We use texture-atlas depth to guess if user wants
        //          LCD subpixel rendering
        if( self->rendermode != RENDER_NORMAL && self->rendermode != RENDER_SIGNED_DISTANCE_FIELD )
        {
            flags |= FT_LOAD_NO_BITMAP;
        }
        else
        {
            flags |= FT_LOAD_RENDER;
        }
        if( !self->hinting )
        {
            flags |= FT_LOAD_NO_HINTING | FT_LOAD_NO_AUTOHINT;
        }
        else
        {
            flags |= FT_LOAD_FORCE_AUTOHINT;
        }
        if( self->atlas->depth == 3 )
        {
            FT_Library_SetLcdFilter( library, FT_LCD_FILTER_LIGHT );
            flags |= FT_LOAD_TARGET_LCD;
            if( self->filtering )
            {
                FT_Library_SetLcdFilterWeights( library, self->lcd_weights );
            }
        }
        error = FT_Load_Glyph( face, glyph_index, flags );
        if( error )
        {
            fprintf( stderr, "FT_Error (line %d, code 0x%02x) : %s\n",
            __LINE__, FT_Errors[error].code, FT_Errors[error].message );
            FT_Done_Face( face );
            FT_Done_FreeType( library );
            return 0;
        }
        if( self->rendermode == RENDER_NORMAL || self->rendermode == RENDER_SIGNED_DISTANCE_FIELD )
        {
            slot            = face->glyph;
            ft_bitmap       = slot->bitmap;
            ft_glyph_top    = slot->bitmap_top;
            ft_glyph_left   = slot->bitmap_left;
        }
        else
        {
            FT_Stroker stroker;
            FT_BitmapGlyph ft_bitmap_glyph;
            error = FT_Stroker_New( library, &stroker );
            if( error )
            {
                fprintf(stderr, "FT_Error (0x%02x) : %s\n",
                FT_Errors[error].code, FT_Errors[error].message);
                goto cleanup_stroker;
            }
            FT_Stroker_Set(stroker,
            (int)(self->outline_thickness * HRES),
            FT_STROKER_LINECAP_ROUND,
            FT_STROKER_LINEJOIN_ROUND,
            0);
            error = FT_Get_Glyph( face->glyph, &ft_glyph);
            if( error )
            {
                fprintf(stderr, "FT_Error (0x%02x) : %s\n",
                FT_Errors[error].code, FT_Errors[error].message);
                goto cleanup_stroker;
            }
            if( self->rendermode == RENDER_OUTLINE_EDGE )
            error = FT_Glyph_Stroke( &ft_glyph, stroker, 1 );
            else if ( self->rendermode == RENDER_OUTLINE_POSITIVE )
            error = FT_Glyph_StrokeBorder( &ft_glyph, stroker, 0, 1 );
            else if ( self->rendermode == RENDER_OUTLINE_NEGATIVE )
            error = FT_Glyph_StrokeBorder( &ft_glyph, stroker, 1, 1 );
            if( error )
            {
                fprintf(stderr, "FT_Error (0x%02x) : %s\n",
                FT_Errors[error].code, FT_Errors[error].message);
                goto cleanup_stroker;
            }
            if( self->atlas->depth == 1 )
            error = FT_Glyph_To_Bitmap( &ft_glyph, FT_RENDER_MODE_NORMAL, 0, 1);
            else
            error = FT_Glyph_To_Bitmap( &ft_glyph, FT_RENDER_MODE_LCD, 0, 1);
            if( error )
            {
                fprintf(stderr, "FT_Error (0x%02x) : %s\n",
                FT_Errors[error].code, FT_Errors[error].message);
                goto cleanup_stroker;
            }
            ft_bitmap_glyph = (FT_BitmapGlyph) ft_glyph;
            ft_bitmap       = ft_bitmap_glyph->bitmap;
            ft_glyph_top    = ft_bitmap_glyph->top;
            ft_glyph_left   = ft_bitmap_glyph->left;
            cleanup_stroker:
            FT_Stroker_Done( stroker );
            if( error )
            {
                FT_Done_Face( face );
                FT_Done_FreeType( library );
                return 0;
            }
        }
        struct {
            int left;
            int top;
            int right;
            int bottom;
        } padding = { 0, 0, 1, 1 };
        if( self->rendermode == RENDER_SIGNED_DISTANCE_FIELD )
        {
            padding.top = 1;
            padding.left = 1;
        }
        size_t src_w = ft_bitmap.width/self->atlas->depth;
        size_t src_h = ft_bitmap.rows;
        size_t tgt_w = src_w + padding.left + padding.right;
        size_t tgt_h = src_h + padding.top + padding.bottom;
        region = texture_atlas_get_region( self->atlas, tgt_w, tgt_h );
        if ( region.x < 0 )
        {
            fprintf( stderr, "Texture atlas is full (line %d)\n",  __LINE__ );
            FT_Done_Face( face );
            FT_Done_FreeType( library );
            return 0;
        }
        x = region.x;
        y = region.y;
        unsigned char *buffer = calloc( tgt_w * tgt_h * self->atlas->depth, sizeof(unsigned char) );
        unsigned char *dst_ptr = buffer + (padding.top * tgt_w + padding.left) * self->atlas->depth;
        unsigned char *src_ptr = ft_bitmap.buffer;
        for( i = 0; i < src_h; i++ )
        {
            //difference between width and pitch: https://www.freetype.org/freetype2/docs/reference/ft2-basic_types.html
            memcpy( dst_ptr, src_ptr, ft_bitmap.width);
            dst_ptr += tgt_w * self->atlas->depth;
            src_ptr += ft_bitmap.pitch;
        }
        if( self->rendermode == RENDER_SIGNED_DISTANCE_FIELD )
        {
            unsigned char *sdf = make_distance_mapb( buffer, (unsigned int)tgt_w, (unsigned int)tgt_h );
            free( buffer );
            buffer = sdf;
        }
        texture_atlas_set_region( self->atlas, x, y, tgt_w, tgt_h, buffer, tgt_w * self->atlas->depth);
        free( buffer );
        glyph = texture_glyph_new( );
        glyph->codepoint = utf8_to_utf32( codepoint );
        glyph->width    = tgt_w;
        glyph->height   = tgt_h;
        glyph->rendermode = self->rendermode;
        glyph->outline_thickness = self->outline_thickness;
        glyph->offset_x = ft_glyph_left;
        glyph->offset_y = ft_glyph_top;
        glyph->s0       = x/(float)self->atlas->width;
        glyph->t0       = y/(float)self->atlas->height;
        glyph->s1       = (x + glyph->width)/(float)self->atlas->width;
        glyph->t1       = (y + glyph->height)/(float)self->atlas->height;
        // Discard hinting to get advance
        FT_Load_Glyph( face, glyph_index, FT_LOAD_RENDER | FT_LOAD_NO_HINTING);
        slot = face->glyph;
        glyph->advance_x = slot->advance.x / HRESf;
        glyph->advance_y = slot->advance.y / HRESf;
        vector_push_back( self->glyphs, &glyph );
        if( self->rendermode != RENDER_NORMAL && self->rendermode != RENDER_SIGNED_DISTANCE_FIELD )
        FT_Done_Glyph( ft_glyph );
        texture_font_generate_kerning( self, &library, &face );
        FT_Done_Face( face );
        FT_Done_FreeType( library );
        return 1;
    }
    // ----------------------------------------------- texture_font_load_glyphs ---
    size_t
    texture_font_load_glyphs( texture_font_t * self,
    const char * codepoints )
    {
        size_t i;
        /* Load each glyph */
        for( i = 0; i < strlen(codepoints); i += utf8_surrogate_len(codepoints + i) ) {
            if( !texture_font_load_glyph( self, codepoints + i ) )
            return utf8_strlen( codepoints + i );
        }
        return 0;
    }
    // ------------------------------------------------- texture_font_get_glyph ---
    texture_glyph_t *
    texture_font_get_glyph( texture_font_t * self,
    const char * codepoint )
    {
        texture_glyph_t *glyph;
        assert( self );
        assert( self->filename );
        assert( self->atlas );
        /* Check if codepoint has been already loaded */
        if( (glyph = texture_font_find_glyph( self, codepoint )) )
        return glyph;
        /* Glyph has not been already loaded */
        if( texture_font_load_glyph( self, codepoint ) )
        return texture_font_find_glyph( self, codepoint );
        return NULL;
    }
    // ------------------------------------------------- texture_font_enlarge_atlas ---
    void
    texture_font_enlarge_atlas( texture_font_t * self, size_t width_new,
    size_t height_new)
    {
        assert(self);
        assert(self->atlas);
        //ensure size increased
        assert(width_new >= self->atlas->width);
        assert(height_new >= self->atlas->height);
        assert(width_new + height_new > self->atlas->width + self->atlas->height);
        texture_atlas_t* ta = self->atlas;
        size_t width_old = ta->width;
        size_t height_old = ta->height;
        //allocate new buffer
        unsigned char* data_old = ta->data;
        ta->data = calloc(1,width_new*height_new * sizeof(char)*ta->depth);
        //update atlas size
        ta->width = width_new;
        ta->height = height_new;
        //add node reflecting the gained space on the right
        if(width_new>width_old){
            ivec3 node;
            node.x = (int)(width_old - 1);
            node.y = 1;
            node.z = (int)(width_new - width_old);
            vector_push_back(ta->nodes, &node);
        }
        //over data from the old buffer, skipping first row and column because of the margin
        size_t pixel_size = sizeof(char) * ta->depth;
        size_t old_row_size = width_old * pixel_size;
        texture_atlas_set_region(ta, 1, 1, width_old - 2, height_old - 2, data_old + old_row_size + pixel_size, old_row_size);
        free(data_old);
        //change uv coordinates of existing glyphs to reflect size change
        float mulw = (float)width_old / width_new;
        float mulh = (float)height_old / height_new;
        size_t i;
        for (i = 0; i < vector_size(self->glyphs); i++) {
            texture_glyph_t* g = *(texture_glyph_t**)vector_get(self->glyphs, i);
            g->s0 *= mulw;
            g->s1 *= mulw;
            g->t0 *= mulh;
            g->t1 *= mulh;
        }
    }
    // ----------------------------------------------------- utf8_surrogate_len ---
    size_t
    utf8_surrogate_len( const char* character )
    {
        size_t result = 0;
        char test_char;
        if (!character)
        return 0;
        test_char = character[0];
        if ((test_char & 0x80) == 0)
        return 1;
        while (test_char & 0x80)
        {
            test_char <<= 1;
            result++;
        }
        return result;
    }
    // ------------------------------------------------------------ utf8_strlen ---
    size_t
    utf8_strlen( const char* string )
    {
        const char* ptr = string;
        size_t result = 0;
        while (*ptr)
        {
            ptr += utf8_surrogate_len(ptr);
            result++;
        }
        return result;
    }
    uint32_t
    utf8_to_utf32( const char * character )
    {
        uint32_t result = -1;
        if( !character )
        {
            return result;
        }
        if( ( character[0] & 0x80 ) == 0x0 )
        {
            result = character[0];
        }
        if( ( character[0] & 0xC0 ) == 0xC0 )
        {
            result = ( ( character[0] & 0x3F ) << 6 ) | ( character[1] & 0x3F );
        }
        if( ( character[0] & 0xE0 ) == 0xE0 )
        {
            result = ( ( character[0] & 0x1F ) << ( 6 + 6 ) ) | ( ( character[1] & 0x3F ) << 6 ) | ( character[2] & 0x3F );
        }
        if( ( character[0] & 0xF0 ) == 0xF0 )
        {
            result = ( ( character[0] & 0x0F ) << ( 6 + 6 + 6 ) ) | ( ( character[1] & 0x3F ) << ( 6 + 6 ) ) | ( ( character[2] & 0x3F ) << 6 ) | ( character[3] & 0x3F );
        }
        if( ( character[0] & 0xF8 ) == 0xF8 )
        {
            result = ( ( character[0] & 0x07 ) << ( 6 + 6 + 6 + 6 ) ) | ( ( character[1] & 0x3F ) << ( 6 + 6 + 6 ) ) | ( ( character[2] & 0x3F ) << ( 6 + 6 ) ) | ( ( character[3] & 0x3F ) << 6 ) | ( character[4] & 0x3F );
        }
        return result;
    }
    // ------------------------------------------------------------- vector_new ---
    vector_t *
    vector_new( size_t item_size )
    {
        vector_t *self = (vector_t *) malloc( sizeof(vector_t) );
        assert( item_size );
        if( !self )
        {
            halt("line %d: No more memory for allocating data\n", __LINE__ );
        }
        self->item_size = item_size;
        self->size      = 0;
        self->capacity  = 1;
        self->items     = malloc( self->item_size * self->capacity );
        return self;
    }
    // ---------------------------------------------------------- vector_delete ---
    void
    vector_delete( vector_t *self )
    {
        assert( self );
        free( self->items );
        free( self );
    }
    // ------------------------------------------------------------- vector_get ---
    const void *
    vector_get( const vector_t *self,
    size_t index )
    {
        assert( self );
        assert( self->size );
        assert( index  < self->size );
        return (char*)(self->items) + index * self->item_size;
    }
    // ----------------------------------------------------------- vector_front ---
    const void *
    vector_front( const vector_t *self )
    {
        assert( self );
        assert( self->size );
        return vector_get( self, 0 );
    }
    // ------------------------------------------------------------ vector_back ---
    const void *
    vector_back( const vector_t *self )
    {
        assert( self );
        assert( self->size );
        return vector_get( self, self->size-1 );
    }
    // -------------------------------------------------------- vector_contains ---
    int
    vector_contains( const vector_t *self,
    const void *item,
    int (*cmp)(const void *, const void *) )
    {
        size_t i;
        assert( self );
        for( i=0; i<self->size; ++i )
        {
            if( (*cmp)(item, vector_get(self,i) ) == 0 )
            {
                return 1;
            }
        }
        return 0;
    }
    // ----------------------------------------------------------- vector_empty ---
    int
    vector_empty( const vector_t *self )
    {
        assert( self );
        return self->size == 0;
    }
    // ------------------------------------------------------------ vector_size ---
    size_t
    vector_size( const vector_t *self )
    {
        assert( self );
        return self->size;
    }
    // --------------------------------------------------------- vector_reserve ---
    void
    vector_reserve( vector_t *self,
    const size_t size )
    {
        assert( self );
        if( self->capacity < size)
        {
            self->items = realloc( self->items, size * self->item_size );
            self->capacity = size;
        }
    }
    // -------------------------------------------------------- vector_capacity ---
    size_t
    vector_capacity( const vector_t *self )
    {
        assert( self );
        return self->capacity;
    }
    // ---------------------------------------------------------- vector_shrink ---
    void
    vector_shrink( vector_t *self )
    {
        assert( self );
        if( self->capacity > self->size )
        {
            self->items = realloc( self->items, self->size * self->item_size );
        }
        self->capacity = self->size;
    }
    // ----------------------------------------------------------- vector_clear ---
    void
    vector_clear( vector_t *self )
    {
        assert( self );
        self->size = 0;
    }
    // ------------------------------------------------------------- vector_set ---
    void
    vector_set( vector_t *self,
    const size_t index,
    const void *item )
    {
        assert( self );
        assert( self->size );
        assert( index  < self->size );
        memcpy( (char *)(self->items) + index * self->item_size,
        item, self->item_size );
    }
    // ---------------------------------------------------------- vector_insert ---
    void
    vector_insert( vector_t *self,
    const size_t index,
    const void *item )
    {
        assert( self );
        assert( index <= self->size);
        if( self->capacity <= self->size )
        {
            vector_reserve(self, 2 * self->capacity );
        }
        if( index < self->size )
        {
            memmove( (char *)(self->items) + (index + 1) * self->item_size,
            (char *)(self->items) + (index + 0) * self->item_size,
            (self->size - index)  * self->item_size);
        }
        self->size++;
        vector_set( self, index, item );
    }
    // ----------------------------------------------------- vector_erase_range ---
    void
    vector_erase_range( vector_t *self,
    const size_t first,
    const size_t last )
    {
        assert( self );
        assert( first < self->size );
        assert( last  < self->size+1 );
        assert( first < last );
        memmove( (char *)(self->items) + first * self->item_size,
        (char *)(self->items) + last  * self->item_size,
        (self->size - last)   * self->item_size);
        self->size -= (last-first);
    }
    // ----------------------------------------------------------- vector_erase ---
    void
    vector_erase( vector_t *self,
    const size_t index )
    {
        assert( self );
        assert( index < self->size );
        vector_erase_range( self, index, index+1 );
    }
    // ------------------------------------------------------- vector_push_back ---
    void
    vector_push_back( vector_t *self,
    const void *item )
    {
        vector_insert( self, self->size, item );
    }
    // -------------------------------------------------------- vector_pop_back ---
    void
    vector_pop_back( vector_t *self )
    {
        assert( self );
        assert( self->size );
        self->size--;
    }
    // ---------------------------------------------------------- vector_resize ---
    void
    vector_resize( vector_t *self,
    const size_t size )
    {
        assert( self );
        if( size > self->capacity)
        {
            vector_reserve( self, size );
            self->size = self->capacity;
        }
        else
        {
            self->size = size;
        }
    }
    // -------------------------------------------------- vector_push_back_data ---
    void
    vector_push_back_data( vector_t *self,
    const void * data,
    const size_t count )
    {
        assert( self );
        assert( data );
        assert( count );
        if( self->capacity < (self->size+count) )
        {
            vector_reserve(self, self->size+count);
        }
        memmove( (char *)(self->items) + self->size * self->item_size, data,
        count*self->item_size );
        self->size += count;
    }
    // ----------------------------------------------------- vector_insert_data ---
    void
    vector_insert_data( vector_t *self,
    const size_t index,
    const void * data,
    const size_t count )
    {
        assert( self );
        assert( index < self->size );
        assert( data );
        assert( count );
        if( self->capacity < (self->size+count) )
        {
            vector_reserve(self, self->size+count);
        }
        memmove( (char *)(self->items) + (index + count ) * self->item_size,
        (char *)(self->items) + (index ) * self->item_size,
        count*self->item_size );
        memmove( (char *)(self->items) + index * self->item_size, data,
        count*self->item_size );
        self->size += count;
    }
    // ------------------------------------------------------------ vector_sort ---
    void
    vector_sort( vector_t *self,
    int (*cmp)(const void *, const void *) )
    {
        assert( self );
        assert( self->size );
        qsort(self->items, self->size, self->item_size, cmp);
    }
    // ----------------------------------------------------------------------------
    vertex_attribute_t *
    vertex_attribute_new( GLchar * name,
    GLint size,
    GLenum type,
    GLboolean normalized,
    GLsizei stride,
    GLvoid *pointer )
    {
        vertex_attribute_t *attribute =
        (vertex_attribute_t *) malloc (sizeof(vertex_attribute_t));
        assert( size > 0 );
        attribute->name       = (GLchar *) strdup( name );
        attribute->index      = -1;
        attribute->size       = size;
        attribute->type       = type;
        attribute->normalized = normalized;
        attribute->stride     = stride;
        attribute->pointer    = pointer;
        return attribute;
    }
    // ----------------------------------------------------------------------------
    void
    vertex_attribute_delete( vertex_attribute_t * self )
    {
        assert( self );
        free( self->name );
        free( self );
    }
    // ----------------------------------------------------------------------------
    vertex_attribute_t *
    vertex_attribute_parse( char *format )
    {
        GLenum type = 0;
        int size;
        int normalized = 0;
        char ctype;
        char *name;
        vertex_attribute_t *attr;
        char *p = strchr(format, ':');
        if( p != NULL)
        {
            name = strndup(format, p-format);
            if( *(++p) == '\0' )
            {
                fprintf( stderr, "No size specified for '%s' attribute\n", name );
                free( name );
                return 0;
            }
            size = *p - '0';
            if( *(++p) == '\0' )
            {
                fprintf( stderr, "No format specified for '%s' attribute\n", name );
                free( name );
                return 0;
            }
            ctype = *p;
            if( *(++p) != '\0' )
            {
                if( *p == 'n' )
                {
                    normalized = 1;
                }
            }
        }
        else
        {
            fprintf(stderr, "Vertex attribute format not understood ('%s')\n", format );
            return 0;
        }
        switch( ctype )
        {
            case 'b': type = GL_BYTE;           break;
            case 'B': type = GL_UNSIGNED_BYTE;  break;
            case 's': type = GL_SHORT;          break;
            case 'S': type = GL_UNSIGNED_SHORT; break;
            case 'i': type = GL_INT;            break;
            case 'I': type = GL_UNSIGNED_INT;   break;
            case 'f': type = GL_FLOAT;          break;
            default:  type = 0;                 break;
        }
        attr = vertex_attribute_new( name, size, type, normalized, 0, 0 );
        free( name );
        return attr;
    }
    // ----------------------------------------------------------------------------
    void
    vertex_attribute_enable( vertex_attribute_t *attr )
    {
        if( attr->index == -1 )
        {
            GLint program;
            glGetIntegerv( GL_CURRENT_PROGRAM, &program );
            if( program == 0)
            {
                return;
            }
            attr->index = glGetAttribLocation( program, attr->name );
            if( attr->index == -1 )
            {
                return;
            }
        }
        glEnableVertexAttribArray( attr->index );
        glVertexAttribPointer( attr->index, attr->size, attr->type,
        attr->normalized, attr->stride, attr->pointer );
    }
    #ifdef WIN32
    // strndup() is not available on Windows
    char *strndup( const char *s1, size_t n)
    {
        char *copy= (char*)malloc( n+1 );
        memcpy( copy, s1, n );
        copy[n] = 0;
        return copy;
    };
    #endif
    /**
    * Buffer status
    */
    #define CLEAN  (0)
    #define DIRTY  (1)
    #define FROZEN (2)
    // ----------------------------------------------------------------------------
    vertex_buffer_t *
    vertex_buffer_new( const char *format )
    {
        size_t i, index = 0, stride = 0;
        const char *start = 0, *end = 0;
        GLchar *pointer = 0;
        vertex_buffer_t *self = (vertex_buffer_t *) malloc (sizeof(vertex_buffer_t));
        if( !self )
        {
            return NULL;
        }
        self->format = strdup( format );
        for( i=0; i<MAX_VERTEX_ATTRIBUTE; ++i )
        {
            self->attributes[i] = 0;
        }
        start = format;
        do
        {
            char *desc = 0;
            vertex_attribute_t *attribute;
            GLuint attribute_size = 0;
            end = (char *) (strchr(start+1, ','));
            if (end == NULL)
            {
                desc = strdup( start );
            }
            else
            {
                desc = strndup( start, end-start );
            }
            attribute = vertex_attribute_parse( desc );
            start = end+1;
            free(desc);
            attribute->pointer = pointer;
            switch( attribute->type )
            {
                case GL_BOOL:           attribute_size = sizeof(GLboolean); break;
                case GL_BYTE:           attribute_size = sizeof(GLbyte); break;
                case GL_UNSIGNED_BYTE:  attribute_size = sizeof(GLubyte); break;
                case GL_SHORT:          attribute_size = sizeof(GLshort); break;
                case GL_UNSIGNED_SHORT: attribute_size = sizeof(GLushort); break;
                case GL_INT:            attribute_size = sizeof(GLint); break;
                case GL_UNSIGNED_INT:   attribute_size = sizeof(GLuint); break;
                case GL_FLOAT:          attribute_size = sizeof(GLfloat); break;
                default:                attribute_size = 0;
            }
            stride  += attribute->size*attribute_size;
            pointer += attribute->size*attribute_size;
            self->attributes[index] = attribute;
            index++;
        } while ( end && (index < MAX_VERTEX_ATTRIBUTE) );
        for( i=0; i<index; ++i )
        {
            self->attributes[i]->stride = (GLsizei)stride;
        }
        #ifdef FREETYPE_GL_USE_VAO
        self->VAO_id = 0;
        #endif
        self->vertices = vector_new( stride );
        self->vertices_id  = 0;
        self->GPU_vsize = 0;
        self->indices = vector_new( sizeof(GLuint) );
        self->indices_id  = 0;
        self->GPU_isize = 0;
        self->items = vector_new( sizeof(ivec4) );
        self->state = DIRTY;
        self->mode = GL_TRIANGLES;
        return self;
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_delete( vertex_buffer_t *self )
    {
        size_t i;
        assert( self );
        for( i=0; i<MAX_VERTEX_ATTRIBUTE; ++i )
        {
            if( self->attributes[i] )
            {
                vertex_attribute_delete( self->attributes[i] );
            }
        }
        #ifdef FREETYPE_GL_USE_VAO
        if( self->VAO_id )
        {
            glDeleteVertexArrays( 1, &self->VAO_id );
        }
        self->VAO_id = 0;
        #endif
        vector_delete( self->vertices );
        self->vertices = 0;
        if( self->vertices_id )
        {
            glDeleteBuffers( 1, &self->vertices_id );
        }
        self->vertices_id = 0;
        vector_delete( self->indices );
        self->indices = 0;
        if( self->indices_id )
        {
            glDeleteBuffers( 1, &self->indices_id );
        }
        self->indices_id = 0;
        vector_delete( self->items );
        if( self->format )
        {
            free( self->format );
        }
        self->format = 0;
        self->state = 0;
        free( self );
    }
    // ----------------------------------------------------------------------------
    const char *
    vertex_buffer_format( const vertex_buffer_t *self )
    {
        assert( self );
        return self->format;
    }
    // ----------------------------------------------------------------------------
    size_t
    vertex_buffer_size( const vertex_buffer_t *self )
    {
        assert( self );
        return vector_size( self->items );
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_print( vertex_buffer_t * self )
    {
        int i = 0;
        static char *gltypes[9] = {
            "GL_BOOL",
            "GL_BYTE",
            "GL_UNSIGNED_BYTE",
            "GL_SHORT",
            "GL_UNSIGNED_SHORT",
            "GL_INT",
            "GL_UNSIGNED_INT",
            "GL_FLOAT",
            "GL_VOID"
        };
        assert(self);
        fprintf( stderr, "%d vertices, %d indices\n",
        (int)vector_size( self->vertices ), (int)vector_size( self->indices ) );
        while( self->attributes[i] )
        {
            int j = 8;
            switch( self->attributes[i]->type )
            {
                case GL_BOOL:           j=0; break;
                case GL_BYTE:           j=1; break;
                case GL_UNSIGNED_BYTE:  j=2; break;
                case GL_SHORT:          j=3; break;
                case GL_UNSIGNED_SHORT: j=4; break;
                case GL_INT:            j=5; break;
                case GL_UNSIGNED_INT:   j=6; break;
                case GL_FLOAT:          j=7; break;
                default:                j=8; break;
            }
            fprintf(stderr, "%s : %dx%s (+%p)\n",
            self->attributes[i]->name,
            self->attributes[i]->size,
            gltypes[j],
            self->attributes[i]->pointer);
            i += 1;
        }
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_upload ( vertex_buffer_t *self )
    {
        size_t vsize, isize;
        if( self->state == FROZEN )
        {
            return;
        }
        if( !self->vertices_id )
        {
            glGenBuffers( 1, &self->vertices_id );
        }
        if( !self->indices_id )
        {
            glGenBuffers( 1, &self->indices_id );
        }
        vsize = self->vertices->size*self->vertices->item_size;
        isize = self->indices->size*self->indices->item_size;
        // Always upload vertices first such that indices do not point to non
        // existing data (if we get interrupted in between for example).
        // Upload vertices
        glBindBuffer( GL_ARRAY_BUFFER, self->vertices_id );
        if( vsize != self->GPU_vsize )
        {
            glBufferData( GL_ARRAY_BUFFER,
            vsize, self->vertices->items, GL_DYNAMIC_DRAW );
            self->GPU_vsize = vsize;
        }
        else
        {
            glBufferSubData( GL_ARRAY_BUFFER,
            0, vsize, self->vertices->items );
        }
        glBindBuffer( GL_ARRAY_BUFFER, 0 );
        // Upload indices
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, self->indices_id );
        if( isize != self->GPU_isize )
        {
            glBufferData( GL_ELEMENT_ARRAY_BUFFER,
            isize, self->indices->items, GL_DYNAMIC_DRAW );
            self->GPU_isize = isize;
        }
        else
        {
            glBufferSubData( GL_ELEMENT_ARRAY_BUFFER,
            0, isize, self->indices->items );
        }
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_clear( vertex_buffer_t *self )
    {
        assert( self );
        self->state = FROZEN;
        vector_clear( self->indices );
        vector_clear( self->vertices );
        vector_clear( self->items );
        self->state = DIRTY;
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_render_setup ( vertex_buffer_t *self, GLenum mode )
    {
        size_t i;
        #ifdef FREETYPE_GL_USE_VAO
        // Unbind so no existing VAO-state is overwritten,
        // (e.g. the GL_ELEMENT_ARRAY_BUFFER-binding).
        glBindVertexArray( 0 );
        #endif
        if( self->state != CLEAN )
        {
            vertex_buffer_upload( self );
            self->state = CLEAN;
        }
        #ifdef FREETYPE_GL_USE_VAO
        if( self->VAO_id == 0 )
        {
            // Generate and set up VAO
            glGenVertexArrays( 1, &self->VAO_id );
            glBindVertexArray( self->VAO_id );
            glBindBuffer( GL_ARRAY_BUFFER, self->vertices_id );
            for( i=0; i<MAX_VERTEX_ATTRIBUTE; ++i )
            {
                vertex_attribute_t *attribute = self->attributes[i];
                if( attribute == 0 )
                {
                    continue;
                }
                else
                {
                    vertex_attribute_enable( attribute );
                }
            }
            glBindBuffer( GL_ARRAY_BUFFER, 0 );
            if( self->indices->size )
            {
                glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, self->indices_id );
            }
        }
        // Bind VAO for drawing
        glBindVertexArray( self->VAO_id );
        #else
        glBindBuffer( GL_ARRAY_BUFFER, self->vertices_id );
        for( i=0; i<MAX_VERTEX_ATTRIBUTE; ++i )
        {
            vertex_attribute_t *attribute = self->attributes[i];
            if ( attribute == 0 )
            {
                continue;
            }
            else
            {
                vertex_attribute_enable( attribute );
            }
        }
        if( self->indices->size )
        {
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, self->indices_id );
        }
        #endif
        self->mode = mode;
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_render_finish ( vertex_buffer_t *self )
    {
        #ifdef FREETYPE_GL_USE_VAO
        glBindVertexArray( 0 );
        #else
        int i;
        for( i=0; i<MAX_VERTEX_ATTRIBUTE; ++i )
        {
            vertex_attribute_t *attribute = self->attributes[i];
            if( attribute == 0 )
            {
                continue;
            }
            else
            {
                glDisableVertexAttribArray( attribute->index );
            }
        }
        glBindBuffer( GL_ARRAY_BUFFER, 0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
        #endif
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_render_item ( vertex_buffer_t *self,
    size_t index )
    {
        ivec4 * item = (ivec4 *) vector_get( self->items, index );
        assert( self );
        assert( index < vector_size( self->items ) );
        if( self->indices->size )
        {
            size_t start = item->istart;
            size_t count = item->icount;
            glDrawElements( self->mode, (GLint)count, GL_UNSIGNED_INT, (void *)(start*sizeof(GLuint)) );
        }
        else if( self->vertices->size )
        {
            size_t start = item->vstart;
            size_t count = item->vcount;
            glDrawArrays( self->mode, (GLint)(start*self->vertices->item_size), (GLint)count);
        }
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_render ( vertex_buffer_t *self, GLenum mode )
    {
        size_t vcount = self->vertices->size;
        size_t icount = self->indices->size;
        vertex_buffer_render_setup( self, mode );
        if( icount )
        {
            glDrawElements( mode, (GLint)icount, GL_UNSIGNED_INT, 0 );
        }
        else
        {
            glDrawArrays( mode, 0, (GLint)vcount );
        }
        vertex_buffer_render_finish( self );
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_push_back_indices ( vertex_buffer_t * self,
    const GLuint * indices,
    const size_t icount )
    {
        assert( self );
        self->state |= DIRTY;
        vector_push_back_data( self->indices, indices, icount );
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_push_back_vertices ( vertex_buffer_t * self,
    const void * vertices,
    const size_t vcount )
    {
        assert( self );
        self->state |= DIRTY;
        vector_push_back_data( self->vertices, vertices, vcount );
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_insert_indices ( vertex_buffer_t *self,
    const size_t index,
    const GLuint *indices,
    const size_t count )
    {
        assert( self );
        assert( self->indices );
        assert( index < self->indices->size+1 );
        self->state |= DIRTY;
        vector_insert_data( self->indices, index, indices, count );
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_insert_vertices( vertex_buffer_t *self,
    const size_t index,
    const void *vertices,
    const size_t vcount )
    {
        size_t i;
        assert( self );
        assert( self->vertices );
        assert( index < self->vertices->size+1 );
        self->state |= DIRTY;
        for( i=0; i<self->indices->size; ++i )
        {
            if( *(GLuint *)(vector_get( self->indices, i )) > index )
            {
                *(GLuint *)(vector_get( self->indices, i )) += index;
            }
        }
        vector_insert_data( self->vertices, index, vertices, vcount );
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_erase_indices( vertex_buffer_t *self,
    const size_t first,
    const size_t last )
    {
        assert( self );
        assert( self->indices );
        assert( first < self->indices->size );
        assert( (last) <= self->indices->size );
        self->state |= DIRTY;
        vector_erase_range( self->indices, first, last );
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_erase_vertices( vertex_buffer_t *self,
    const size_t first,
    const size_t last )
    {
        size_t i;
        assert( self );
        assert( self->vertices );
        assert( first < self->vertices->size );
        assert( last <= self->vertices->size );
        assert( last > first );
        self->state |= DIRTY;
        for( i=0; i<self->indices->size; ++i )
        {
            if( *(GLuint *)(vector_get( self->indices, i )) > first )
            {
                *(GLuint *)(vector_get( self->indices, i )) -= (last-first);
            }
        }
        vector_erase_range( self->vertices, first, last );
    }
    // ----------------------------------------------------------------------------
    size_t
    vertex_buffer_push_back( vertex_buffer_t * self,
    const void * vertices, const size_t vcount,
    const GLuint * indices, const size_t icount )
    {
        return vertex_buffer_insert( self, vector_size( self->items ),
        vertices, vcount, indices, icount );
    }
    // ----------------------------------------------------------------------------
    size_t
    vertex_buffer_insert( vertex_buffer_t * self, const size_t index,
    const void * vertices, const size_t vcount,
    const GLuint * indices, const size_t icount )
    {
        size_t vstart, istart, i;
        ivec4 item;
        assert( self );
        assert( vertices );
        assert( indices );
        self->state = FROZEN;
        // Push back vertices
        vstart = vector_size( self->vertices );
        vertex_buffer_push_back_vertices( self, vertices, vcount );
        // Push back indices
        istart = vector_size( self->indices );
        vertex_buffer_push_back_indices( self, indices, icount );
        // Update indices within the vertex buffer
        for( i=0; i<icount; ++i )
        {
            *(GLuint *)(vector_get( self->indices, istart+i )) += vstart;
        }
        // Insert item
        item.x = (int)vstart;
        item.y = (int)vcount;
        item.z = (int)istart;
        item.w = (int)icount;
        vector_insert( self->items, index, &item );
        self->state = DIRTY;
        return index;
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_erase( vertex_buffer_t * self,
    const size_t index )
    {
        ivec4 * item;
        int vstart;
        size_t vcount, istart, icount, i;
        assert( self );
        assert( index < vector_size( self->items ) );
        item = (ivec4 *) vector_get( self->items, index );
        vstart = item->vstart;
        vcount = item->vcount;
        istart = item->istart;
        icount = item->icount;
        // Update items
        for( i=0; i<vector_size(self->items); ++i )
        {
            ivec4 * item = (ivec4 *) vector_get( self->items, i );
            if( item->vstart > vstart)
            {
                item->vstart -= vcount;
                item->istart -= icount;
            }
        }
        self->state = FROZEN;
        vertex_buffer_erase_indices( self, istart, istart+icount );
        vertex_buffer_erase_vertices( self, vstart, vstart+vcount );
        vector_erase( self->items, index );
        self->state = DIRTY;
    }
    #include <lib/ui/obj_parser.c>
void sjf_animator(sjs_animator* _this) {
}

void sjf_animator_copy(sjs_animator* _this, sjs_animator* _from) {
    _this->animations._refCount = 1;
#line 27 "lib/ui/animation.sj"
    sjf_list_heap_iface_animation_copy(&_this->animations, &_from->animations);
#line 27
    _this->current = _from->current;
}

void sjf_animator_destroy(sjs_animator* _this) {
    if (_this->animations._refCount == 1) { sjf_list_heap_iface_animation_destroy(&_this->animations); }
;
}

void sjf_animator_heap(sjs_animator* _this) {
}

void sjf_animator_nextframe(sjs_animator* _parent, int32_t time) {
    int32_t sjt_capture137;
    sjs_list_heap_iface_animation* sjt_parent186 = 0;

#line 31 "lib/ui/animation.sj"
    _parent->current = time;
#line 4 "lib/common/list.sj"
    sjt_parent186 = &_parent->animations;
#line 4
    sjf_list_heap_iface_animation_getcount(sjt_parent186, &sjt_capture137);
    if (sjt_capture137 > 0) {
        int32_t i;
        int32_t sjt_forEnd21;
        int32_t sjt_forStart21;
        sjs_list_heap_iface_animation* sjt_parent187 = 0;

#line 35 "lib/ui/animation.sj"
        sjt_forStart21 = 0;
#line 4 "lib/common/list.sj"
        sjt_parent187 = &_parent->animations;
#line 4
        sjf_list_heap_iface_animation_getcount(sjt_parent187, &sjt_forEnd21);
#line 35 "lib/ui/animation.sj"
        i = sjt_forEnd21 - 1;
        while (i >= sjt_forStart21) {
            sji_animation a = { 0 };
            bool sjt_capture138;
            int32_t sjt_functionParam484;
            int32_t sjt_interfaceParam1;
            sjs_list_heap_iface_animation* sjt_parent189 = 0;
            sji_animation sjt_parent190 = { 0 };

#line 8 "lib/common/list.sj"
            sjt_parent189 = &_parent->animations;
#line 35 "lib/ui/animation.sj"
            sjt_functionParam484 = i;
#line 35
            sjf_list_heap_iface_animation_getat_heap(sjt_parent189, sjt_functionParam484, &a);
#line 2
            sjt_parent190 = a;
#line 31
            sjt_interfaceParam1 = time;
#line 37
            sjt_parent190._vtbl->nextframe(sjt_parent190._parent, sjt_interfaceParam1, &sjt_capture138);
            if (sjt_capture138) {
                int32_t sjt_functionParam485;
                sjs_list_heap_iface_animation* sjt_parent191 = 0;

#line 53 "lib/common/list.sj"
                sjt_parent191 = &_parent->animations;
#line 35 "lib/ui/animation.sj"
                sjt_functionParam485 = i;
#line 35
                sjf_list_heap_iface_animation_removeat(sjt_parent191, sjt_functionParam485);
            }

#line 35
            i--;

            if (a._parent != 0) {
                a._parent->_refCount--;
                if (a._parent->_refCount <= 0) {
                    a._vtbl->destroy(a._parent);
                    free(a._parent);
                }
            }
        }
    }
}

void sjf_array_bool(sjs_array_bool* _this) {
#line 309 "lib/common/array.sj"
    if (_this->datasize < 0) {
#line 310
        halt("size is less than zero");
#line 311
    }
#line 313
    if (!_this->data) {
#line 314
        _this->data = (int*)malloc(_this->datasize * sizeof(bool) + sizeof(int)) + 1;
#line 315
        int* refcount = (int*)_this->data - 1;
#line 316
        *refcount = 1;
#line 317
        if (!_this->data) {
#line 318
            halt("grow: out of memory\n");
#line 319
        }
#line 320
    }
}

void sjf_array_bool_copy(sjs_array_bool* _this, sjs_array_bool* _from) {
#line 1 "lib/common/array.sj"
    _this->datasize = _from->datasize;
#line 1
    _this->data = _from->data;
#line 1
    _this->isglobal = _from->isglobal;
#line 1
    _this->count = _from->count;
#line 325
    _this->data = _from->data;
#line 326
    if (!_this->isglobal && _this->data) {
#line 327
        int* refcount = (int*)_this->data - 1;
#line 328
        *refcount = *refcount + 1;
#line 329
    }
}

void sjf_array_bool_destroy(sjs_array_bool* _this) {
#line 333 "lib/common/array.sj"
    if (!_this->isglobal && _this->data) {
#line 334
        int* refcount = (int*)_this->data - 1;
#line 335
        *refcount = *refcount - 1;
#line 336
        if (*refcount == 0) {
#line 337
            #if !true && !false
#line 338
            bool* p = (bool*)_this->data;
#line 339
            for (int i = 0; i < _this->count; i++) {
#line 340
                ;
#line 341
            }
#line 342
            #endif
#line 343
            free(refcount);
#line 344
        }
#line 345
    }
}

void sjf_array_bool_getat(sjs_array_bool* _parent, int32_t index, bool* _return) {
#line 9 "lib/common/array.sj"
    if (index >= _parent->count || index < 0) {
#line 10
        halt("getAt: out of bounds\n");
#line 11
    }
#line 13
    bool* p = (bool*)_parent->data;
#line 14
    #line 8 "lib/common/array.sj"
(*_return) = p[index];
return;;       
}

void sjf_array_bool_heap(sjs_array_bool* _this) {
#line 309 "lib/common/array.sj"
    if (_this->datasize < 0) {
#line 310
        halt("size is less than zero");
#line 311
    }
#line 313
    if (!_this->data) {
#line 314
        _this->data = (int*)malloc(_this->datasize * sizeof(bool) + sizeof(int)) + 1;
#line 315
        int* refcount = (int*)_this->data - 1;
#line 316
        *refcount = 1;
#line 317
        if (!_this->data) {
#line 318
            halt("grow: out of memory\n");
#line 319
        }
#line 320
    }
}

void sjf_array_bool_initat(sjs_array_bool* _parent, int32_t index, bool item) {
#line 36 "lib/common/array.sj"
    if (index != _parent->count) {
#line 37
        halt("initAt: can only initialize last element\n");     
#line 38
    }
#line 39
    if (index >= _parent->datasize || index < 0) {
#line 40
        halt("initAt: out of bounds %d:%d\n", index, _parent->datasize);
#line 41
    }
#line 43
    bool* p = (bool*)_parent->data;
#line 44
    #line 34 "lib/common/array.sj"
p[index] = item;
;
#line 45
    _parent->count = index + 1;
}

void sjf_array_bool_setat(sjs_array_bool* _parent, int32_t index, bool item) {
#line 51 "lib/common/array.sj"
    if (index >= _parent->count || index < 0) {
#line 52
        halt("setAt: out of bounds %d:%d\n", index, _parent->count);
#line 53
    }
#line 55
    bool* p = (bool*)_parent->data;
#line 56
    ;
#line 57
    #line 49 "lib/common/array.sj"
p[index] = item;
;
}

void sjf_array_char(sjs_array_char* _this) {
#line 309 "lib/common/array.sj"
    if (_this->datasize < 0) {
#line 310
        halt("size is less than zero");
#line 311
    }
#line 313
    if (!_this->data) {
#line 314
        _this->data = (int*)malloc(_this->datasize * sizeof(char) + sizeof(int)) + 1;
#line 315
        int* refcount = (int*)_this->data - 1;
#line 316
        *refcount = 1;
#line 317
        if (!_this->data) {
#line 318
            halt("grow: out of memory\n");
#line 319
        }
#line 320
    }
}

void sjf_array_char_copy(sjs_array_char* _this, sjs_array_char* _from) {
#line 1 "lib/common/array.sj"
    _this->datasize = _from->datasize;
#line 1
    _this->data = _from->data;
#line 1
    _this->isglobal = _from->isglobal;
#line 1
    _this->count = _from->count;
#line 325
    _this->data = _from->data;
#line 326
    if (!_this->isglobal && _this->data) {
#line 327
        int* refcount = (int*)_this->data - 1;
#line 328
        *refcount = *refcount + 1;
#line 329
    }
}

void sjf_array_char_destroy(sjs_array_char* _this) {
#line 333 "lib/common/array.sj"
    if (!_this->isglobal && _this->data) {
#line 334
        int* refcount = (int*)_this->data - 1;
#line 335
        *refcount = *refcount - 1;
#line 336
        if (*refcount == 0) {
#line 337
            #if !true && !false
#line 338
            char* p = (char*)_this->data;
#line 339
            for (int i = 0; i < _this->count; i++) {
#line 340
                ;
#line 341
            }
#line 342
            #endif
#line 343
            free(refcount);
#line 344
        }
#line 345
    }
}

void sjf_array_char_getat(sjs_array_char* _parent, int32_t index, char* _return) {
#line 9 "lib/common/array.sj"
    if (index >= _parent->count || index < 0) {
#line 10
        halt("getAt: out of bounds\n");
#line 11
    }
#line 13
    char* p = (char*)_parent->data;
#line 14
    #line 8 "lib/common/array.sj"
(*_return) = p[index];
return;;       
}

void sjf_array_char_grow(sjs_array_char* _parent, int32_t newsize, sjs_array_char* _return) {
    void* newdata;

#line 135 "lib/common/array.sj"
    newdata = 0;
#line 137
    if (_parent->datasize != newsize) {
#line 138
        if (newsize < _parent->datasize) {
#line 139
            halt("grow: new size smaller than old _parent->datasize %d:%d\n", newsize, _parent->datasize);
#line 140
        }
#line 142
        newdata = (int*)(malloc(sizeof(int) + newsize * sizeof(char))) + 1;
#line 143
        int* refcount = (int*)newdata - 1;
#line 144
        *refcount = 1;
#line 146
        if (!_parent->data) {
#line 147
            halt("grow: out of memory\n");
#line 148
        }
#line 150
        char* p = (char*)_parent->data;
#line 151
        char* newp = (char*)newdata;
#line 153
        int count = _parent->count;
#line 155
        #if true
#line 156
        memcpy(newp, p, sizeof(char) * count);
#line 157
        #else
#line 158
        for (int i = 0; i < count; i++) {
#line 159
            #line 136 "lib/common/array.sj"
newp[i] = p[i];
;
#line 160
        }
#line 161
        #endif
#line 162
    }
#line 162
    _return->_refCount = 1;
#line 134
    _return->datasize = newsize;
#line 164
    _return->data = newdata;
#line 4
    _return->isglobal = false;
#line 164
    _return->count = _parent->count;
#line 164
    sjf_array_char(_return);
}

void sjf_array_char_grow_heap(sjs_array_char* _parent, int32_t newsize, sjs_array_char** _return) {
    void* newdata;

#line 135 "lib/common/array.sj"
    newdata = 0;
#line 137
    if (_parent->datasize != newsize) {
#line 138
        if (newsize < _parent->datasize) {
#line 139
            halt("grow: new size smaller than old _parent->datasize %d:%d\n", newsize, _parent->datasize);
#line 140
        }
#line 142
        newdata = (int*)(malloc(sizeof(int) + newsize * sizeof(char))) + 1;
#line 143
        int* refcount = (int*)newdata - 1;
#line 144
        *refcount = 1;
#line 146
        if (!_parent->data) {
#line 147
            halt("grow: out of memory\n");
#line 148
        }
#line 150
        char* p = (char*)_parent->data;
#line 151
        char* newp = (char*)newdata;
#line 153
        int count = _parent->count;
#line 155
        #if true
#line 156
        memcpy(newp, p, sizeof(char) * count);
#line 157
        #else
#line 158
        for (int i = 0; i < count; i++) {
#line 159
            #line 136 "lib/common/array.sj"
newp[i] = p[i];
;
#line 160
        }
#line 161
        #endif
#line 162
    }
#line 162
    (*_return) = (sjs_array_char*)malloc(sizeof(sjs_array_char));
#line 162
    (*_return)->_refCount = 1;
#line 134
    (*_return)->datasize = newsize;
#line 164
    (*_return)->data = newdata;
#line 4
    (*_return)->isglobal = false;
#line 164
    (*_return)->count = _parent->count;
#line 164
    sjf_array_char_heap((*_return));
}

void sjf_array_char_heap(sjs_array_char* _this) {
#line 309 "lib/common/array.sj"
    if (_this->datasize < 0) {
#line 310
        halt("size is less than zero");
#line 311
    }
#line 313
    if (!_this->data) {
#line 314
        _this->data = (int*)malloc(_this->datasize * sizeof(char) + sizeof(int)) + 1;
#line 315
        int* refcount = (int*)_this->data - 1;
#line 316
        *refcount = 1;
#line 317
        if (!_this->data) {
#line 318
            halt("grow: out of memory\n");
#line 319
        }
#line 320
    }
}

void sjf_array_char_initat(sjs_array_char* _parent, int32_t index, char item) {
#line 36 "lib/common/array.sj"
    if (index != _parent->count) {
#line 37
        halt("initAt: can only initialize last element\n");     
#line 38
    }
#line 39
    if (index >= _parent->datasize || index < 0) {
#line 40
        halt("initAt: out of bounds %d:%d\n", index, _parent->datasize);
#line 41
    }
#line 43
    char* p = (char*)_parent->data;
#line 44
    #line 34 "lib/common/array.sj"
p[index] = item;
;
#line 45
    _parent->count = index + 1;
}

void sjf_array_char_isequal(sjs_array_char* _parent, sjs_array_char* test, bool* _return) {
#line 271 "lib/common/array.sj"
    if (_parent->count != test->count) {
#line 272
        *_return = false;
#line 273
    }
#line 275
    bool result = memcmp(_parent->data, test->data, _parent->count * sizeof(char)) == 0;
#line 276
    #line 270 "lib/common/array.sj"
(*_return) = result;
return;;      
}

void sjf_array_f32(sjs_array_f32* _this) {
#line 309 "lib/common/array.sj"
    if (_this->datasize < 0) {
#line 310
        halt("size is less than zero");
#line 311
    }
#line 313
    if (!_this->data) {
#line 314
        _this->data = (int*)malloc(_this->datasize * sizeof(float) + sizeof(int)) + 1;
#line 315
        int* refcount = (int*)_this->data - 1;
#line 316
        *refcount = 1;
#line 317
        if (!_this->data) {
#line 318
            halt("grow: out of memory\n");
#line 319
        }
#line 320
    }
}

void sjf_array_f32_copy(sjs_array_f32* _this, sjs_array_f32* _from) {
#line 1 "lib/common/array.sj"
    _this->datasize = _from->datasize;
#line 1
    _this->data = _from->data;
#line 1
    _this->isglobal = _from->isglobal;
#line 1
    _this->count = _from->count;
#line 325
    _this->data = _from->data;
#line 326
    if (!_this->isglobal && _this->data) {
#line 327
        int* refcount = (int*)_this->data - 1;
#line 328
        *refcount = *refcount + 1;
#line 329
    }
}

void sjf_array_f32_destroy(sjs_array_f32* _this) {
#line 333 "lib/common/array.sj"
    if (!_this->isglobal && _this->data) {
#line 334
        int* refcount = (int*)_this->data - 1;
#line 335
        *refcount = *refcount - 1;
#line 336
        if (*refcount == 0) {
#line 337
            #if !true && !false
#line 338
            float* p = (float*)_this->data;
#line 339
            for (int i = 0; i < _this->count; i++) {
#line 340
                ;
#line 341
            }
#line 342
            #endif
#line 343
            free(refcount);
#line 344
        }
#line 345
    }
}

void sjf_array_f32_getat(sjs_array_f32* _parent, int32_t index, float* _return) {
#line 9 "lib/common/array.sj"
    if (index >= _parent->count || index < 0) {
#line 10
        halt("getAt: out of bounds\n");
#line 11
    }
#line 13
    float* p = (float*)_parent->data;
#line 14
    #line 8 "lib/common/array.sj"
(*_return) = p[index];
return;;       
}

void sjf_array_f32_heap(sjs_array_f32* _this) {
#line 309 "lib/common/array.sj"
    if (_this->datasize < 0) {
#line 310
        halt("size is less than zero");
#line 311
    }
#line 313
    if (!_this->data) {
#line 314
        _this->data = (int*)malloc(_this->datasize * sizeof(float) + sizeof(int)) + 1;
#line 315
        int* refcount = (int*)_this->data - 1;
#line 316
        *refcount = 1;
#line 317
        if (!_this->data) {
#line 318
            halt("grow: out of memory\n");
#line 319
        }
#line 320
    }
}

void sjf_array_f32_init(sjs_array_f32* _parent, float item, sjs_array_f32* _return) {
#line 20 "lib/common/array.sj"
    if (0 != _parent->count) {
#line 21
        halt("init: can only initialize a completely uninitialized list\n");     
#line 22
    }
#line 24
    float* p = (float*)_parent->data;
#line 25
    int count = _parent->datasize;
#line 26
    for (int i = 0; i < count; i++) {
#line 27
        #line 18 "lib/common/array.sj"
p[i] = item;
;
#line 28
    }
#line 29
    _parent->count = _parent->datasize;  
#line 29
    _return->_refCount = 1;
#line 31
    sjf_array_f32_copy(_return, _parent);
}

void sjf_array_f32_init_heap(sjs_array_f32* _parent, float item, sjs_array_f32** _return) {
#line 20 "lib/common/array.sj"
    if (0 != _parent->count) {
#line 21
        halt("init: can only initialize a completely uninitialized list\n");     
#line 22
    }
#line 24
    float* p = (float*)_parent->data;
#line 25
    int count = _parent->datasize;
#line 26
    for (int i = 0; i < count; i++) {
#line 27
        #line 18 "lib/common/array.sj"
p[i] = item;
;
#line 28
    }
#line 29
    _parent->count = _parent->datasize;  
#line 29
    (*_return) = (sjs_array_f32*)malloc(sizeof(sjs_array_f32));
#line 29
    (*_return)->_refCount = 1;
#line 31
    sjf_array_f32_copy((*_return), _parent);
}

void sjf_array_f32_setat(sjs_array_f32* _parent, int32_t index, float item) {
#line 51 "lib/common/array.sj"
    if (index >= _parent->count || index < 0) {
#line 52
        halt("setAt: out of bounds %d:%d\n", index, _parent->count);
#line 53
    }
#line 55
    float* p = (float*)_parent->data;
#line 56
    ;
#line 57
    #line 49 "lib/common/array.sj"
p[index] = item;
;
}

void sjf_array_heap_iface_animation(sjs_array_heap_iface_animation* _this) {
#line 309 "lib/common/array.sj"
    if (_this->datasize < 0) {
#line 310
        halt("size is less than zero");
#line 311
    }
#line 313
    if (!_this->data) {
#line 314
        _this->data = (int*)malloc(_this->datasize * sizeof(sji_animation) + sizeof(int)) + 1;
#line 315
        int* refcount = (int*)_this->data - 1;
#line 316
        *refcount = 1;
#line 317
        if (!_this->data) {
#line 318
            halt("grow: out of memory\n");
#line 319
        }
#line 320
    }
}

void sjf_array_heap_iface_animation_copy(sjs_array_heap_iface_animation* _this, sjs_array_heap_iface_animation* _from) {
#line 1 "lib/common/array.sj"
    _this->datasize = _from->datasize;
#line 1
    _this->data = _from->data;
#line 1
    _this->isglobal = _from->isglobal;
#line 1
    _this->count = _from->count;
#line 325
    _this->data = _from->data;
#line 326
    if (!_this->isglobal && _this->data) {
#line 327
        int* refcount = (int*)_this->data - 1;
#line 328
        *refcount = *refcount + 1;
#line 329
    }
}

void sjf_array_heap_iface_animation_destroy(sjs_array_heap_iface_animation* _this) {
#line 333 "lib/common/array.sj"
    if (!_this->isglobal && _this->data) {
#line 334
        int* refcount = (int*)_this->data - 1;
#line 335
        *refcount = *refcount - 1;
#line 336
        if (*refcount == 0) {
#line 337
            #if !false && !false
#line 338
            sji_animation* p = (sji_animation*)_this->data;
#line 339
            for (int i = 0; i < _this->count; i++) {
#line 340
                if (p[i]._parent != 0) {
    p[i]._parent->_refCount--;
    if (p[i]._parent->_refCount <= 0) {
        p[i]._vtbl->destroy(p[i]._parent);
        free(p[i]._parent);
    }
}
;
#line 341
            }
#line 342
            #endif
#line 343
            free(refcount);
#line 344
        }
#line 345
    }
}

void sjf_array_heap_iface_animation_getat_heap(sjs_array_heap_iface_animation* _parent, int32_t index, sji_animation* _return) {
#line 9 "lib/common/array.sj"
    if (index >= _parent->count || index < 0) {
#line 10
        halt("getAt: out of bounds\n");
#line 11
    }
#line 13
    sji_animation* p = (sji_animation*)_parent->data;
#line 14
    #line 8 "lib/common/array.sj"
(*_return) = p[index];
if ((*_return)._parent != 0) {
    (*_return)._parent->_refCount++;
}
return;;       
}

void sjf_array_heap_iface_animation_heap(sjs_array_heap_iface_animation* _this) {
#line 309 "lib/common/array.sj"
    if (_this->datasize < 0) {
#line 310
        halt("size is less than zero");
#line 311
    }
#line 313
    if (!_this->data) {
#line 314
        _this->data = (int*)malloc(_this->datasize * sizeof(sji_animation) + sizeof(int)) + 1;
#line 315
        int* refcount = (int*)_this->data - 1;
#line 316
        *refcount = 1;
#line 317
        if (!_this->data) {
#line 318
            halt("grow: out of memory\n");
#line 319
        }
#line 320
    }
}

void sjf_array_heap_iface_model(sjs_array_heap_iface_model* _this) {
#line 309 "lib/common/array.sj"
    if (_this->datasize < 0) {
#line 310
        halt("size is less than zero");
#line 311
    }
#line 313
    if (!_this->data) {
#line 314
        _this->data = (int*)malloc(_this->datasize * sizeof(sji_model) + sizeof(int)) + 1;
#line 315
        int* refcount = (int*)_this->data - 1;
#line 316
        *refcount = 1;
#line 317
        if (!_this->data) {
#line 318
            halt("grow: out of memory\n");
#line 319
        }
#line 320
    }
}

void sjf_array_heap_iface_model_copy(sjs_array_heap_iface_model* _this, sjs_array_heap_iface_model* _from) {
#line 1 "lib/common/array.sj"
    _this->datasize = _from->datasize;
#line 1
    _this->data = _from->data;
#line 1
    _this->isglobal = _from->isglobal;
#line 1
    _this->count = _from->count;
#line 325
    _this->data = _from->data;
#line 326
    if (!_this->isglobal && _this->data) {
#line 327
        int* refcount = (int*)_this->data - 1;
#line 328
        *refcount = *refcount + 1;
#line 329
    }
}

void sjf_array_heap_iface_model_destroy(sjs_array_heap_iface_model* _this) {
#line 333 "lib/common/array.sj"
    if (!_this->isglobal && _this->data) {
#line 334
        int* refcount = (int*)_this->data - 1;
#line 335
        *refcount = *refcount - 1;
#line 336
        if (*refcount == 0) {
#line 337
            #if !false && !false
#line 338
            sji_model* p = (sji_model*)_this->data;
#line 339
            for (int i = 0; i < _this->count; i++) {
#line 340
                if (p[i]._parent != 0) {
    p[i]._parent->_refCount--;
    if (p[i]._parent->_refCount <= 0) {
        p[i]._vtbl->destroy(p[i]._parent);
        free(p[i]._parent);
    }
}
;
#line 341
            }
#line 342
            #endif
#line 343
            free(refcount);
#line 344
        }
#line 345
    }
}

void sjf_array_heap_iface_model_heap(sjs_array_heap_iface_model* _this) {
#line 309 "lib/common/array.sj"
    if (_this->datasize < 0) {
#line 310
        halt("size is less than zero");
#line 311
    }
#line 313
    if (!_this->data) {
#line 314
        _this->data = (int*)malloc(_this->datasize * sizeof(sji_model) + sizeof(int)) + 1;
#line 315
        int* refcount = (int*)_this->data - 1;
#line 316
        *refcount = 1;
#line 317
        if (!_this->data) {
#line 318
            halt("grow: out of memory\n");
#line 319
        }
#line 320
    }
}

void sjf_array_rect(sjs_array_rect* _this) {
#line 309 "lib/common/array.sj"
    if (_this->datasize < 0) {
#line 310
        halt("size is less than zero");
#line 311
    }
#line 313
    if (!_this->data) {
#line 314
        _this->data = (int*)malloc(_this->datasize * sizeof(sjs_rect) + sizeof(int)) + 1;
#line 315
        int* refcount = (int*)_this->data - 1;
#line 316
        *refcount = 1;
#line 317
        if (!_this->data) {
#line 318
            halt("grow: out of memory\n");
#line 319
        }
#line 320
    }
}

void sjf_array_rect_copy(sjs_array_rect* _this, sjs_array_rect* _from) {
#line 1 "lib/common/array.sj"
    _this->datasize = _from->datasize;
#line 1
    _this->data = _from->data;
#line 1
    _this->isglobal = _from->isglobal;
#line 1
    _this->count = _from->count;
#line 325
    _this->data = _from->data;
#line 326
    if (!_this->isglobal && _this->data) {
#line 327
        int* refcount = (int*)_this->data - 1;
#line 328
        *refcount = *refcount + 1;
#line 329
    }
}

void sjf_array_rect_destroy(sjs_array_rect* _this) {
#line 333 "lib/common/array.sj"
    if (!_this->isglobal && _this->data) {
#line 334
        int* refcount = (int*)_this->data - 1;
#line 335
        *refcount = *refcount - 1;
#line 336
        if (*refcount == 0) {
#line 337
            #if !false && !true
#line 338
            sjs_rect* p = (sjs_rect*)_this->data;
#line 339
            for (int i = 0; i < _this->count; i++) {
#line 340
                ;
#line 341
            }
#line 342
            #endif
#line 343
            free(refcount);
#line 344
        }
#line 345
    }
}

void sjf_array_rect_getat(sjs_array_rect* _parent, int32_t index, sjs_rect* _return) {
#line 9 "lib/common/array.sj"
    if (index >= _parent->count || index < 0) {
#line 10
        halt("getAt: out of bounds\n");
#line 11
    }
#line 13
    sjs_rect* p = (sjs_rect*)_parent->data;
#line 14
    _return->_refCount = 1;
#line 8 "lib/common/array.sj"
sjf_rect_copy(_return, &p[index]);
return;;       
}

void sjf_array_rect_getat_heap(sjs_array_rect* _parent, int32_t index, sjs_rect** _return) {
#line 9 "lib/common/array.sj"
    if (index >= _parent->count || index < 0) {
#line 10
        halt("getAt: out of bounds\n");
#line 11
    }
#line 13
    sjs_rect* p = (sjs_rect*)_parent->data;
#line 14
    (*_return) = (sjs_rect*)malloc(sizeof(sjs_rect));
(*_return)->_refCount = 1;
#line 8 "lib/common/array.sj"
sjf_rect_copy((*_return), &p[index]);
return;;       
}

void sjf_array_rect_grow(sjs_array_rect* _parent, int32_t newsize, sjs_array_rect* _return) {
    void* newdata;

#line 135 "lib/common/array.sj"
    newdata = 0;
#line 137
    if (_parent->datasize != newsize) {
#line 138
        if (newsize < _parent->datasize) {
#line 139
            halt("grow: new size smaller than old _parent->datasize %d:%d\n", newsize, _parent->datasize);
#line 140
        }
#line 142
        newdata = (int*)(malloc(sizeof(int) + newsize * sizeof(sjs_rect))) + 1;
#line 143
        int* refcount = (int*)newdata - 1;
#line 144
        *refcount = 1;
#line 146
        if (!_parent->data) {
#line 147
            halt("grow: out of memory\n");
#line 148
        }
#line 150
        sjs_rect* p = (sjs_rect*)_parent->data;
#line 151
        sjs_rect* newp = (sjs_rect*)newdata;
#line 153
        int count = _parent->count;
#line 155
        #if false
#line 156
        memcpy(newp, p, sizeof(sjs_rect) * count);
#line 157
        #else
#line 158
        for (int i = 0; i < count; i++) {
#line 159
            newp[i]._refCount = 1;
#line 136 "lib/common/array.sj"
sjf_rect_copy(&newp[i], &p[i]);
;
#line 160
        }
#line 161
        #endif
#line 162
    }
#line 162
    _return->_refCount = 1;
#line 134
    _return->datasize = newsize;
#line 164
    _return->data = newdata;
#line 4
    _return->isglobal = false;
#line 164
    _return->count = _parent->count;
#line 164
    sjf_array_rect(_return);
}

void sjf_array_rect_grow_heap(sjs_array_rect* _parent, int32_t newsize, sjs_array_rect** _return) {
    void* newdata;

#line 135 "lib/common/array.sj"
    newdata = 0;
#line 137
    if (_parent->datasize != newsize) {
#line 138
        if (newsize < _parent->datasize) {
#line 139
            halt("grow: new size smaller than old _parent->datasize %d:%d\n", newsize, _parent->datasize);
#line 140
        }
#line 142
        newdata = (int*)(malloc(sizeof(int) + newsize * sizeof(sjs_rect))) + 1;
#line 143
        int* refcount = (int*)newdata - 1;
#line 144
        *refcount = 1;
#line 146
        if (!_parent->data) {
#line 147
            halt("grow: out of memory\n");
#line 148
        }
#line 150
        sjs_rect* p = (sjs_rect*)_parent->data;
#line 151
        sjs_rect* newp = (sjs_rect*)newdata;
#line 153
        int count = _parent->count;
#line 155
        #if false
#line 156
        memcpy(newp, p, sizeof(sjs_rect) * count);
#line 157
        #else
#line 158
        for (int i = 0; i < count; i++) {
#line 159
            newp[i]._refCount = 1;
#line 136 "lib/common/array.sj"
sjf_rect_copy(&newp[i], &p[i]);
;
#line 160
        }
#line 161
        #endif
#line 162
    }
#line 162
    (*_return) = (sjs_array_rect*)malloc(sizeof(sjs_array_rect));
#line 162
    (*_return)->_refCount = 1;
#line 134
    (*_return)->datasize = newsize;
#line 164
    (*_return)->data = newdata;
#line 4
    (*_return)->isglobal = false;
#line 164
    (*_return)->count = _parent->count;
#line 164
    sjf_array_rect_heap((*_return));
}

void sjf_array_rect_heap(sjs_array_rect* _this) {
#line 309 "lib/common/array.sj"
    if (_this->datasize < 0) {
#line 310
        halt("size is less than zero");
#line 311
    }
#line 313
    if (!_this->data) {
#line 314
        _this->data = (int*)malloc(_this->datasize * sizeof(sjs_rect) + sizeof(int)) + 1;
#line 315
        int* refcount = (int*)_this->data - 1;
#line 316
        *refcount = 1;
#line 317
        if (!_this->data) {
#line 318
            halt("grow: out of memory\n");
#line 319
        }
#line 320
    }
}

void sjf_array_rect_initat(sjs_array_rect* _parent, int32_t index, sjs_rect* item) {
#line 36 "lib/common/array.sj"
    if (index != _parent->count) {
#line 37
        halt("initAt: can only initialize last element\n");     
#line 38
    }
#line 39
    if (index >= _parent->datasize || index < 0) {
#line 40
        halt("initAt: out of bounds %d:%d\n", index, _parent->datasize);
#line 41
    }
#line 43
    sjs_rect* p = (sjs_rect*)_parent->data;
#line 44
    p[index]._refCount = 1;
#line 34 "lib/common/array.sj"
sjf_rect_copy(&p[index], item);
;
#line 45
    _parent->count = index + 1;
}

void sjf_array_u32(sjs_array_u32* _this) {
#line 309 "lib/common/array.sj"
    if (_this->datasize < 0) {
#line 310
        halt("size is less than zero");
#line 311
    }
#line 313
    if (!_this->data) {
#line 314
        _this->data = (int*)malloc(_this->datasize * sizeof(uint32_t) + sizeof(int)) + 1;
#line 315
        int* refcount = (int*)_this->data - 1;
#line 316
        *refcount = 1;
#line 317
        if (!_this->data) {
#line 318
            halt("grow: out of memory\n");
#line 319
        }
#line 320
    }
}

void sjf_array_u32_copy(sjs_array_u32* _this, sjs_array_u32* _from) {
#line 1 "lib/common/array.sj"
    _this->datasize = _from->datasize;
#line 1
    _this->data = _from->data;
#line 1
    _this->isglobal = _from->isglobal;
#line 1
    _this->count = _from->count;
#line 325
    _this->data = _from->data;
#line 326
    if (!_this->isglobal && _this->data) {
#line 327
        int* refcount = (int*)_this->data - 1;
#line 328
        *refcount = *refcount + 1;
#line 329
    }
}

void sjf_array_u32_destroy(sjs_array_u32* _this) {
#line 333 "lib/common/array.sj"
    if (!_this->isglobal && _this->data) {
#line 334
        int* refcount = (int*)_this->data - 1;
#line 335
        *refcount = *refcount - 1;
#line 336
        if (*refcount == 0) {
#line 337
            #if !true && !false
#line 338
            uint32_t* p = (uint32_t*)_this->data;
#line 339
            for (int i = 0; i < _this->count; i++) {
#line 340
                ;
#line 341
            }
#line 342
            #endif
#line 343
            free(refcount);
#line 344
        }
#line 345
    }
}

void sjf_array_u32_heap(sjs_array_u32* _this) {
#line 309 "lib/common/array.sj"
    if (_this->datasize < 0) {
#line 310
        halt("size is less than zero");
#line 311
    }
#line 313
    if (!_this->data) {
#line 314
        _this->data = (int*)malloc(_this->datasize * sizeof(uint32_t) + sizeof(int)) + 1;
#line 315
        int* refcount = (int*)_this->data - 1;
#line 316
        *refcount = 1;
#line 317
        if (!_this->data) {
#line 318
            halt("grow: out of memory\n");
#line 319
        }
#line 320
    }
}

void sjf_color(sjs_color* _this) {
}

void sjf_color_copy(sjs_color* _this, sjs_color* _from) {
#line 10 "lib/ui/color.sj"
    _this->r = _from->r;
#line 10
    _this->g = _from->g;
#line 10
    _this->b = _from->b;
#line 10
    _this->a = _from->a;
}

void sjf_color_destroy(sjs_color* _this) {
}

void sjf_color_heap(sjs_color* _this) {
}

void sjf_debug_writeline(sjs_string* data) {
    sjs_string* sjt_parent195 = 0;

#line 9 "lib/common/debug.sj"
    sjt_parent195 = data;
#line 9
    sjf_string_nullterminate(sjt_parent195);
#line 12
    debugout("%s\n", (char*)data->data.data);
}

void sjf_f32_abs(float v, float* _return) {
#line 83 "lib/common/f32.sj"
    #line 82 "lib/common/f32.sj"
(*_return) = fabsf(v);
return;
}

void sjf_f32_asstring(float val, sjs_string* _return) {
    int32_t count;
    void* data;

#line 94 "lib/common/f32.sj"
    count = 0;
#line 95
    data = 0;
#line 97
    data = (int*)malloc(sizeof(int) + sizeof(char) * 256) + 1;
#line 98
    int* refcount = (int*)data - 1;
#line 99
    *refcount = 1;
#line 100
    snprintf((char*)data, 256, "%f", val);
#line 101
    count = (int)strlen((char*)data);
#line 101
    _return->_refCount = 1;
#line 103
    _return->count = count;
#line 103
    _return->data._refCount = 1;
#line 103
    _return->data.datasize = count;
#line 103
    _return->data.data = data;
#line 4 "lib/common/array.sj"
    _return->data.isglobal = false;
#line 103 "lib/common/f32.sj"
    _return->data.count = count;
#line 103
    sjf_array_char(&_return->data);
#line 14 "lib/common/string.sj"
    _return->_isnullterminated = false;
#line 14
    sjf_string(_return);
}

void sjf_f32_asstring_heap(float val, sjs_string** _return) {
    int32_t count;
    void* data;

#line 94 "lib/common/f32.sj"
    count = 0;
#line 95
    data = 0;
#line 97
    data = (int*)malloc(sizeof(int) + sizeof(char) * 256) + 1;
#line 98
    int* refcount = (int*)data - 1;
#line 99
    *refcount = 1;
#line 100
    snprintf((char*)data, 256, "%f", val);
#line 101
    count = (int)strlen((char*)data);
#line 101
    (*_return) = (sjs_string*)malloc(sizeof(sjs_string));
#line 101
    (*_return)->_refCount = 1;
#line 103
    (*_return)->count = count;
#line 103
    (*_return)->data._refCount = 1;
#line 103
    (*_return)->data.datasize = count;
#line 103
    (*_return)->data.data = data;
#line 4 "lib/common/array.sj"
    (*_return)->data.isglobal = false;
#line 103 "lib/common/f32.sj"
    (*_return)->data.count = count;
#line 103
    sjf_array_char(&(*_return)->data);
#line 14 "lib/common/string.sj"
    (*_return)->_isnullterminated = false;
#line 14
    sjf_string_heap((*_return));
}

void sjf_f32_cos(float v, float* _return) {
    float result;

#line 12 "lib/common/f32.sj"
    result = 0.0f;
#line 14
    result = cosf(v);
#line 11
    (*_return) = result;
}

void sjf_f32_exp(float v, float* _return) {
#line 89 "lib/common/f32.sj"
    #line 88 "lib/common/f32.sj"
(*_return) = expf(v);
return;
}

void sjf_f32_hash(float val, uint32_t* _return) {
    uint32_t result;

#line 107 "lib/common/f32.sj"
    result = (uint32_t)0u;
#line 109
    int32_t* p = (int32_t*)&val;
#line 110
    result = *p;
#line 106
    (*_return) = result;
}

void sjf_f32_pow(float x, float y, float* _return) {
#line 77 "lib/common/f32.sj"
    #line 76 "lib/common/f32.sj"
(*_return) = powf(x, y);
return;;
}

void sjf_f32_sin(float v, float* _return) {
    float result;

#line 20 "lib/common/f32.sj"
    result = 0.0f;
#line 22
    result = sinf(v);
#line 19
    (*_return) = result;
}

void sjf_f32_sqrt(float v, float* _return) {
    float result;

#line 4 "lib/common/f32.sj"
    result = 0.0f;
#line 6
    result = sqrtf(v);
#line 3
    (*_return) = result;
}

void sjf_f32_tan(float v, float* _return) {
    float result;

#line 28 "lib/common/f32.sj"
    result = 0.0f;
#line 30
    result = tanf(v);
#line 27
    (*_return) = result;
}

void sjf_font(sjs_font* _this) {
#line 65 "lib/ui/font.sj"
    _this->atlas = texture_atlas_new( 512, 512, 3 );
#line 66
    _this->font = texture_font_new_from_file(_this->atlas, _this->size, (char*)_this->src.data.data);
#line 67
    if (_this->font == 0) {
#line 68
        printf("texture_font_new_from_file Error\n");
#line 69
    }   
#line 71
    glGenTextures( 1, &_this->atlas->id );
#line 72
    glBindTexture( GL_TEXTURE_2D, _this->atlas->id );
#line 73
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#line 74
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
#line 75
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
#line 76
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
#line 77
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
#line 78
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, (int)_this->atlas->width, (int)_this->atlas->height, 0, GL_RGB, GL_UNSIGNED_BYTE, _this->atlas->data );
}

void sjf_font_copy(sjs_font* _this, sjs_font* _from) {
    _this->src._refCount = 1;
#line 33 "lib/ui/font.sj"
    sjf_string_copy(&_this->src, &_from->src);
#line 33
    _this->size = _from->size;
#line 83
    _this->atlas = _from->atlas;
#line 84
    ptr_retain(_this->atlas);
#line 86
    _this->font = _from->font;
#line 87
    ptr_retain(_this->font);
}

void sjf_font_destroy(sjs_font* _this) {
#line 91 "lib/ui/font.sj"
    if (ptr_release(_this->atlas)) {
#line 92
        texture_atlas_delete(_this->atlas);
#line 93
    }
#line 95
    if (ptr_release(_this->font)) {
#line 96
        texture_font_delete(_this->font);
#line 97
    }
#line 97
    if (_this->src._refCount == 1) { sjf_string_destroy(&_this->src); }
;
}

void sjf_font_heap(sjs_font* _this) {
#line 65 "lib/ui/font.sj"
    _this->atlas = texture_atlas_new( 512, 512, 3 );
#line 66
    _this->font = texture_font_new_from_file(_this->atlas, _this->size, (char*)_this->src.data.data);
#line 67
    if (_this->font == 0) {
#line 68
        printf("texture_font_new_from_file Error\n");
#line 69
    }   
#line 71
    glGenTextures( 1, &_this->atlas->id );
#line 72
    glBindTexture( GL_TEXTURE_2D, _this->atlas->id );
#line 73
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#line 74
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
#line 75
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
#line 76
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
#line 77
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
#line 78
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, (int)_this->atlas->width, (int)_this->atlas->height, 0, GL_RGB, GL_UNSIGNED_BYTE, _this->atlas->data );
}

void sjf_fontkey(sjs_fontkey* _this) {
}

void sjf_fontkey_copy(sjs_fontkey* _this, sjs_fontkey* _from) {
    _this->src._refCount = 1;
#line 20 "lib/ui/font.sj"
    sjf_string_copy(&_this->src, &_from->src);
#line 20
    _this->size = _from->size;
}

void sjf_fontkey_destroy(sjs_fontkey* _this) {
    if (_this->src._refCount == 1) { sjf_string_destroy(&_this->src); }
;
}

void sjf_fontkey_hash(sjs_fontkey* _parent, uint32_t* _return) {
    uint32_t sjt_capture1;
    uint32_t sjt_capture2;
    float sjt_functionParam10;
    sjs_string* sjt_parent2 = 0;

#line 83 "lib/common/string.sj"
    sjt_parent2 = &_parent->src;
#line 83
    sjf_string_hash(sjt_parent2, &sjt_capture1);
#line 25 "lib/ui/font.sj"
    sjt_functionParam10 = _parent->size;
#line 25
    sjf_f32_hash(sjt_functionParam10, &sjt_capture2);
#line 25
    (*_return) = sjt_capture1 ^ sjt_capture2;
}

void sjf_fontkey_heap(sjs_fontkey* _this) {
}

void sjf_fontkey_isequal(sjs_fontkey* _parent, sjs_fontkey* x, bool* _return) {
    bool sjt_capture3;
    sjs_string* sjt_functionParam11 = 0;
    sjs_string* sjt_parent3 = 0;

#line 44 "lib/common/string.sj"
    sjt_parent3 = &_parent->src;
#line 29 "lib/ui/font.sj"
    sjt_functionParam11 = &x->src;
#line 29
    sjf_string_isequal(sjt_parent3, sjt_functionParam11, &sjt_capture3);
    if (sjt_capture3) {
#line 29 "lib/ui/font.sj"
        (*_return) = (_parent->size == x->size);
    } else {
#line 29 "lib/ui/font.sj"
        (*_return) = false;
    }
}

void sjf_glbeginpoints(void) {
#line 17 "perf2.sj"
    glBegin(GL_POINTS);
}

void sjf_glblendfunc(int32_t sfactor, int32_t dfactor) {
#line 285 "lib/ui/gl.sj"
    glBlendFunc(sfactor, dfactor);
}

void sjf_glclearcolor(sjs_color* color) {
#line 279 "lib/ui/gl.sj"
    glClearColor(color->r, color->g, color->b, color->a);
}

void sjf_glcolor3f(float r, float g, float b) {
#line 5 "perf2.sj"
    glColor3f(r, g, b);
}

void sjf_glenable(int32_t feature) {
#line 113 "lib/ui/gl.sj"
    glEnable(feature);
}

void sjf_glend(void) {
#line 23 "perf2.sj"
    glEnd();
}

void sjf_glpopviewport(sjs_rect* rect, sjs_rect* scenerect) {
    sjs_rect newrect = { -1 };
    sjs_rect oldrect = { -1 };
    bool result40;
    sjs_rect sjt_call30 = { -1 };
    sjs_string sjt_call31 = { -1 };
    int32_t sjt_capture141;
    bool sjt_capture142;
    int32_t sjt_capture143;
    int32_t sjt_capture144;
    int32_t sjt_functionParam524;
    sjs_rect* sjt_functionParam525 = 0;
    int32_t sjt_functionParam527;
    sjs_rect* sjt_parent214 = 0;
    sjs_list_rect* sjt_parent217 = 0;
    sjs_list_rect* sjt_parent218 = 0;
    sjs_list_rect* sjt_parent220 = 0;
    sjs_list_rect* sjt_parent221 = 0;
    sjs_list_rect* sjt_parent222 = 0;

    oldrect._refCount = 1;
#line 134 "lib/ui/gl.sj"
    oldrect.x = rect->x;
#line 134
    oldrect.y = scenerect->h - (rect->y + rect->h);
#line 134
    oldrect.w = rect->w;
#line 134
    oldrect.h = rect->h;
#line 134
    sjf_rect(&oldrect);
#line 8 "lib/common/list.sj"
    sjt_parent217 = &g_glviewports;
#line 4
    sjt_parent218 = &g_glviewports;
#line 4
    sjf_list_rect_getcount(sjt_parent218, &sjt_capture141);
#line 135 "lib/ui/gl.sj"
    sjt_functionParam524 = sjt_capture141 - 1;
#line 135
    sjf_list_rect_getat(sjt_parent217, sjt_functionParam524, &sjt_call30);
#line 135
    sjt_parent214 = &sjt_call30;
#line 135
    sjt_functionParam525 = &oldrect;
#line 135
    sjf_rect_isequal(sjt_parent214, sjt_functionParam525, &sjt_capture142);
#line 135
    result40 = !sjt_capture142;
    if (result40) {
        sjs_string* sjt_functionParam526 = 0;

        sjt_call31._refCount = 1;
#line 136 "lib/ui/gl.sj"
        sjt_call31.count = 30;
#line 136
        sjt_call31.data._refCount = 1;
#line 136
        sjt_call31.data.datasize = 30;
#line 136
        sjt_call31.data.data = (void*)sjg_string17;
#line 136
        sjt_call31.data.isglobal = true;
#line 136
        sjt_call31.data.count = 30;
#line 136
        sjf_array_char(&sjt_call31.data);
#line 14 "lib/common/string.sj"
        sjt_call31._isnullterminated = false;
#line 14
        sjf_string(&sjt_call31);
#line 136 "lib/ui/gl.sj"
        sjt_functionParam526 = &sjt_call31;
#line 136
        sjf_halt(sjt_functionParam526);
    }

#line 53 "lib/common/list.sj"
    sjt_parent220 = &g_glviewports;
#line 4
    sjt_parent221 = &g_glviewports;
#line 4
    sjf_list_rect_getcount(sjt_parent221, &sjt_capture143);
#line 138 "lib/ui/gl.sj"
    sjt_functionParam527 = sjt_capture143 - 1;
#line 138
    sjf_list_rect_removeat(sjt_parent220, sjt_functionParam527);
#line 4 "lib/common/list.sj"
    sjt_parent222 = &g_glviewports;
#line 4
    sjf_list_rect_getcount(sjt_parent222, &sjt_capture144);
    if (sjt_capture144 > 0) {
        int32_t sjt_capture145;
        int32_t sjt_functionParam528;
        sjs_list_rect* sjt_parent223 = 0;
        sjs_list_rect* sjt_parent224 = 0;

#line 8 "lib/common/list.sj"
        sjt_parent223 = &g_glviewports;
#line 4
        sjt_parent224 = &g_glviewports;
#line 4
        sjf_list_rect_getcount(sjt_parent224, &sjt_capture145);
#line 139 "lib/ui/gl.sj"
        sjt_functionParam528 = sjt_capture145 - 1;
#line 139
        sjf_list_rect_getat(sjt_parent223, sjt_functionParam528, &newrect);
    } else {
        newrect._refCount = 1;
#line 2 "lib/ui/rect.sj"
        newrect.x = 0;
#line 3
        newrect.y = 0;
#line 4
        newrect.w = 0;
#line 5
        newrect.h = 0;
#line 5
        sjf_rect(&newrect);
    }

#line 141 "lib/ui/gl.sj"
    glViewport(newrect.x, newrect.y, newrect.w, newrect.h);

    if (newrect._refCount == 1) { sjf_rect_destroy(&newrect); }
;
    if (oldrect._refCount == 1) { sjf_rect_destroy(&oldrect); }
;
    if (sjt_call30._refCount == 1) { sjf_rect_destroy(&sjt_call30); }
;
    if (sjt_call31._refCount == 1) { sjf_string_destroy(&sjt_call31); }
;
}

void sjf_glpushviewport(sjs_rect* rect, sjs_rect* scenerect) {
    sjs_rect newrect = { -1 };
    sjs_rect* sjt_functionParam518 = 0;
    sjs_list_rect* sjt_parent209 = 0;

    newrect._refCount = 1;
#line 126 "lib/ui/gl.sj"
    newrect.x = rect->x;
#line 126
    newrect.y = scenerect->h - (rect->y + rect->h);
#line 126
    newrect.w = rect->w;
#line 126
    newrect.h = rect->h;
#line 126
    sjf_rect(&newrect);
#line 44 "lib/common/list.sj"
    sjt_parent209 = &g_glviewports;
#line 127 "lib/ui/gl.sj"
    sjt_functionParam518 = &newrect;
#line 127
    sjf_list_rect_add(sjt_parent209, sjt_functionParam518);
#line 129
    glViewport(newrect.x, newrect.y, newrect.w, newrect.h);

    if (newrect._refCount == 1) { sjf_rect_destroy(&newrect); }
;
}

void sjf_glrotated(float r, float x, float y, float z) {
#line 11 "perf2.sj"
    glRotated(r, x, y, z);
}

void sjf_glvertex3f(float x, float y, float z) {
#line 29 "perf2.sj"
    glVertex3f(x, y, z);
}

void sjf_halt(sjs_string* reason) {
    sjs_string* sjt_parent219 = 0;

#line 1 "lib/common/halt.sj"
    sjt_parent219 = reason;
#line 1
    sjf_string_nullterminate(sjt_parent219);
#line 4
    halt("%s\n", (char*)reason->data.data);
}

void sjf_hash_fontkey_weak_font(sjs_hash_fontkey_weak_font* _this) {
#line 225 "lib/common/hash.sj"
    _this->_hash = kh_init(fontkey_weak_font_hash_type);
}

void sjf_hash_fontkey_weak_font__weakptrremovekey(sjs_hash_fontkey_weak_font* _parent, sjs_fontkey* key) {
#line 180 "lib/common/hash.sj"
    #if false
#line 181
    khash_t(fontkey_weak_font_hash_type)* p = (khash_t(fontkey_weak_font_hash_type)*)_parent->_hash;    
#line 182
    khiter_t k = kh_get(fontkey_weak_font_hash_type, p, key);
#line 183
    if (k != kh_end(p)) {
#line 184
        kh_del(fontkey_weak_font_hash_type, p, k);
#line 185
    }
#line 186
    #endif
}

void sjf_hash_fontkey_weak_font__weakptrremovevalue(sjs_hash_fontkey_weak_font* _parent, sjs_font* val) {
#line 192 "lib/common/hash.sj"
    #if true
#line 193
    khash_t(fontkey_weak_font_hash_type)* p = (khash_t(fontkey_weak_font_hash_type)*)_parent->_hash;
#line 194
    for (khiter_t k = kh_begin(p); k != kh_end(p); ++k) {
#line 195
        if (kh_exist(p, k)) {
#line 196
            sjs_font* t = kh_value(p, k);
#line 197
            if (t == val) {
#line 198
                kh_del(fontkey_weak_font_hash_type, p, k);
#line 199
            }
#line 200
        }
#line 201
    }
#line 202
    #endif
}

void sjf_hash_fontkey_weak_font_copy(sjs_hash_fontkey_weak_font* _this, sjs_hash_fontkey_weak_font* _from) {
#line 230 "lib/common/hash.sj"
    _this->_hash = _from->_hash;
#line 231
    khash_t(fontkey_weak_font_hash_type)* p = (khash_t(fontkey_weak_font_hash_type)*)_this->_hash;
#line 232
    p->refcount++;
}

void sjf_hash_fontkey_weak_font_destroy(sjs_hash_fontkey_weak_font* _this) {
#line 236 "lib/common/hash.sj"
    khash_t(fontkey_weak_font_hash_type)* p = (khash_t(fontkey_weak_font_hash_type)*)_this->_hash;
#line 237
    p->refcount--;
#line 238
    if (p->refcount == 0) {
#line 239
        for (khiter_t k = kh_begin(p); k != kh_end(p); ++k) {
#line 240
            if (kh_exist(p, k)) {
#line 242
                #if false
#line 243
                delete_cb cb = { p, (void(*)(void*, void*))sjf_hash_fontkey_weak_font__weakptrremovekey };
#line 244
                weakptr_cb_remove(kh_key(p, k), cb);
#line 245
                #else
#line 246
                ;
#line 247
                #endif
#line 249
                #if true
#line 250
                delete_cb cb = { p, (void(*)(void*, void*))sjf_hash_fontkey_weak_font__weakptrremovevalue };
#line 251
                weakptr_cb_remove(kh_value(p, k), cb);
#line 252
                #else
#line 253
                delete_cb weakptrcb9 = { &kh_value(p, k), weakptr_clear };
if (kh_value(p, k) != 0) { weakptr_cb_remove(kh_value(p, k), weakptrcb9); }
;
#line 254
                #endif
#line 255
            }
#line 256
        }
#line 257
        kh_destroy(fontkey_weak_font_hash_type, _this->_hash);
#line 258
    }
}

void sjf_hash_fontkey_weak_font_heap(sjs_hash_fontkey_weak_font* _this) {
#line 225 "lib/common/hash.sj"
    _this->_hash = kh_init(fontkey_weak_font_hash_type);
}

void sjf_hash_string_weak_iface_element(sjs_hash_string_weak_iface_element* _this) {
#line 225 "lib/common/hash.sj"
    _this->_hash = kh_init(string_weak_iface_element_hash_type);
}

void sjf_hash_string_weak_iface_element__weakptrremovekey(sjs_hash_string_weak_iface_element* _parent, sjs_string* key) {
#line 180 "lib/common/hash.sj"
    #if false
#line 181
    khash_t(string_weak_iface_element_hash_type)* p = (khash_t(string_weak_iface_element_hash_type)*)_parent->_hash;    
#line 182
    khiter_t k = kh_get(string_weak_iface_element_hash_type, p, key);
#line 183
    if (k != kh_end(p)) {
#line 184
        kh_del(string_weak_iface_element_hash_type, p, k);
#line 185
    }
#line 186
    #endif
}

void sjf_hash_string_weak_iface_element__weakptrremovevalue(sjs_hash_string_weak_iface_element* _parent, sji_element val) {
#line 192 "lib/common/hash.sj"
    #if true
#line 193
    khash_t(string_weak_iface_element_hash_type)* p = (khash_t(string_weak_iface_element_hash_type)*)_parent->_hash;
#line 194
    for (khiter_t k = kh_begin(p); k != kh_end(p); ++k) {
#line 195
        if (kh_exist(p, k)) {
#line 196
            sji_element t = kh_value(p, k);
#line 197
            if (t._parent == val._parent) {
#line 198
                kh_del(string_weak_iface_element_hash_type, p, k);
#line 199
            }
#line 200
        }
#line 201
    }
#line 202
    #endif
}

void sjf_hash_string_weak_iface_element_copy(sjs_hash_string_weak_iface_element* _this, sjs_hash_string_weak_iface_element* _from) {
#line 230 "lib/common/hash.sj"
    _this->_hash = _from->_hash;
#line 231
    khash_t(string_weak_iface_element_hash_type)* p = (khash_t(string_weak_iface_element_hash_type)*)_this->_hash;
#line 232
    p->refcount++;
}

void sjf_hash_string_weak_iface_element_destroy(sjs_hash_string_weak_iface_element* _this) {
#line 236 "lib/common/hash.sj"
    khash_t(string_weak_iface_element_hash_type)* p = (khash_t(string_weak_iface_element_hash_type)*)_this->_hash;
#line 237
    p->refcount--;
#line 238
    if (p->refcount == 0) {
#line 239
        for (khiter_t k = kh_begin(p); k != kh_end(p); ++k) {
#line 240
            if (kh_exist(p, k)) {
#line 242
                #if false
#line 243
                delete_cb cb = { p, (void(*)(void*, void*))sjf_hash_string_weak_iface_element__weakptrremovekey };
#line 244
                weakptr_cb_remove(kh_key(p, k), cb);
#line 245
                #else
#line 246
                ;
#line 247
                #endif
#line 249
                #if true
#line 250
                delete_cb cb = { p, (void(*)(void*, void*))sjf_hash_string_weak_iface_element__weakptrremovevalue };
#line 251
                weakptr_cb_remove(kh_value(p, k)._parent, cb);
#line 252
                #else
#line 253
                delete_cb weakptrcb8 = { &kh_value(p, k)._parent, weakptr_clear };
if (kh_value(p, k)._parent != 0) { weakptr_cb_remove(kh_value(p, k)._parent, weakptrcb8); }
;
#line 254
                #endif
#line 255
            }
#line 256
        }
#line 257
        kh_destroy(string_weak_iface_element_hash_type, _this->_hash);
#line 258
    }
}

void sjf_hash_string_weak_iface_element_heap(sjs_hash_string_weak_iface_element* _this) {
#line 225 "lib/common/hash.sj"
    _this->_hash = kh_init(string_weak_iface_element_hash_type);
}

void sjf_hash_string_weak_iface_model(sjs_hash_string_weak_iface_model* _this) {
#line 225 "lib/common/hash.sj"
    _this->_hash = kh_init(string_weak_iface_model_hash_type);
}

void sjf_hash_string_weak_iface_model__weakptrremovekey(sjs_hash_string_weak_iface_model* _parent, sjs_string* key) {
#line 180 "lib/common/hash.sj"
    #if false
#line 181
    khash_t(string_weak_iface_model_hash_type)* p = (khash_t(string_weak_iface_model_hash_type)*)_parent->_hash;    
#line 182
    khiter_t k = kh_get(string_weak_iface_model_hash_type, p, key);
#line 183
    if (k != kh_end(p)) {
#line 184
        kh_del(string_weak_iface_model_hash_type, p, k);
#line 185
    }
#line 186
    #endif
}

void sjf_hash_string_weak_iface_model__weakptrremovevalue(sjs_hash_string_weak_iface_model* _parent, sji_model val) {
#line 192 "lib/common/hash.sj"
    #if true
#line 193
    khash_t(string_weak_iface_model_hash_type)* p = (khash_t(string_weak_iface_model_hash_type)*)_parent->_hash;
#line 194
    for (khiter_t k = kh_begin(p); k != kh_end(p); ++k) {
#line 195
        if (kh_exist(p, k)) {
#line 196
            sji_model t = kh_value(p, k);
#line 197
            if (t._parent == val._parent) {
#line 198
                kh_del(string_weak_iface_model_hash_type, p, k);
#line 199
            }
#line 200
        }
#line 201
    }
#line 202
    #endif
}

void sjf_hash_string_weak_iface_model_copy(sjs_hash_string_weak_iface_model* _this, sjs_hash_string_weak_iface_model* _from) {
#line 230 "lib/common/hash.sj"
    _this->_hash = _from->_hash;
#line 231
    khash_t(string_weak_iface_model_hash_type)* p = (khash_t(string_weak_iface_model_hash_type)*)_this->_hash;
#line 232
    p->refcount++;
}

void sjf_hash_string_weak_iface_model_destroy(sjs_hash_string_weak_iface_model* _this) {
#line 236 "lib/common/hash.sj"
    khash_t(string_weak_iface_model_hash_type)* p = (khash_t(string_weak_iface_model_hash_type)*)_this->_hash;
#line 237
    p->refcount--;
#line 238
    if (p->refcount == 0) {
#line 239
        for (khiter_t k = kh_begin(p); k != kh_end(p); ++k) {
#line 240
            if (kh_exist(p, k)) {
#line 242
                #if false
#line 243
                delete_cb cb = { p, (void(*)(void*, void*))sjf_hash_string_weak_iface_model__weakptrremovekey };
#line 244
                weakptr_cb_remove(kh_key(p, k), cb);
#line 245
                #else
#line 246
                ;
#line 247
                #endif
#line 249
                #if true
#line 250
                delete_cb cb = { p, (void(*)(void*, void*))sjf_hash_string_weak_iface_model__weakptrremovevalue };
#line 251
                weakptr_cb_remove(kh_value(p, k)._parent, cb);
#line 252
                #else
#line 253
                delete_cb weakptrcb7 = { &kh_value(p, k)._parent, weakptr_clear };
if (kh_value(p, k)._parent != 0) { weakptr_cb_remove(kh_value(p, k)._parent, weakptrcb7); }
;
#line 254
                #endif
#line 255
            }
#line 256
        }
#line 257
        kh_destroy(string_weak_iface_model_hash_type, _this->_hash);
#line 258
    }
}

void sjf_hash_string_weak_iface_model_heap(sjs_hash_string_weak_iface_model* _this) {
#line 225 "lib/common/hash.sj"
    _this->_hash = kh_init(string_weak_iface_model_hash_type);
}

void sjf_hash_type_bool(sjs_hash_type_bool* _this) {
#line 225 "lib/common/hash.sj"
    _this->_hash = kh_init(type_bool_hash_type);
}

void sjf_hash_type_bool__weakptrremovekey(sjs_hash_type_bool* _parent, int32_t key) {
#line 180 "lib/common/hash.sj"
    #if false
#line 181
    khash_t(type_bool_hash_type)* p = (khash_t(type_bool_hash_type)*)_parent->_hash;    
#line 182
    khiter_t k = kh_get(type_bool_hash_type, p, key);
#line 183
    if (k != kh_end(p)) {
#line 184
        kh_del(type_bool_hash_type, p, k);
#line 185
    }
#line 186
    #endif
}

void sjf_hash_type_bool__weakptrremovevalue(sjs_hash_type_bool* _parent, bool val) {
#line 192 "lib/common/hash.sj"
    #if false
#line 193
    khash_t(type_bool_hash_type)* p = (khash_t(type_bool_hash_type)*)_parent->_hash;
#line 194
    for (khiter_t k = kh_begin(p); k != kh_end(p); ++k) {
#line 195
        if (kh_exist(p, k)) {
#line 196
            bool t = kh_value(p, k);
#line 197
            if (t == val) {
#line 198
                kh_del(type_bool_hash_type, p, k);
#line 199
            }
#line 200
        }
#line 201
    }
#line 202
    #endif
}

void sjf_hash_type_bool_copy(sjs_hash_type_bool* _this, sjs_hash_type_bool* _from) {
#line 230 "lib/common/hash.sj"
    _this->_hash = _from->_hash;
#line 231
    khash_t(type_bool_hash_type)* p = (khash_t(type_bool_hash_type)*)_this->_hash;
#line 232
    p->refcount++;
}

void sjf_hash_type_bool_destroy(sjs_hash_type_bool* _this) {
#line 236 "lib/common/hash.sj"
    khash_t(type_bool_hash_type)* p = (khash_t(type_bool_hash_type)*)_this->_hash;
#line 237
    p->refcount--;
#line 238
    if (p->refcount == 0) {
#line 239
        for (khiter_t k = kh_begin(p); k != kh_end(p); ++k) {
#line 240
            if (kh_exist(p, k)) {
#line 242
                #if false
#line 243
                delete_cb cb = { p, (void(*)(void*, void*))sjf_hash_type_bool__weakptrremovekey };
#line 244
                weakptr_cb_remove(kh_key(p, k), cb);
#line 245
                #else
#line 246
                ;
#line 247
                #endif
#line 249
                #if false
#line 250
                delete_cb cb = { p, (void(*)(void*, void*))sjf_hash_type_bool__weakptrremovevalue };
#line 251
                weakptr_cb_remove(kh_value(p, k), cb);
#line 252
                #else
#line 253
                ;
#line 254
                #endif
#line 255
            }
#line 256
        }
#line 257
        kh_destroy(type_bool_hash_type, _this->_hash);
#line 258
    }
}

void sjf_hash_type_bool_heap(sjs_hash_type_bool* _this) {
#line 225 "lib/common/hash.sj"
    _this->_hash = kh_init(type_bool_hash_type);
}

void sjf_i32_max(int32_t a, int32_t b, int32_t* _return) {
    if (a < b) {
#line 6 "lib/common/i32.sj"
        (*_return) = b;
    } else {
#line 6 "lib/common/i32.sj"
        (*_return) = a;
    }
}

void sjf_light(sjs_light* _this) {
}

void sjf_light_copy(sjs_light* _this, sjs_light* _from) {
    _this->pos._refCount = 1;
#line 1 "lib/ui/scene3dElement.sj"
    sjf_vec3_copy(&_this->pos, &_from->pos);
#line 1
    _this->diffusecolor._refCount = 1;
#line 1
    sjf_color_copy(&_this->diffusecolor, &_from->diffusecolor);
#line 1
    _this->speccolor._refCount = 1;
#line 1
    sjf_color_copy(&_this->speccolor, &_from->speccolor);
}

void sjf_light_destroy(sjs_light* _this) {
    if (_this->pos._refCount == 1) { sjf_vec3_destroy(&_this->pos); }
;
    if (_this->diffusecolor._refCount == 1) { sjf_color_destroy(&_this->diffusecolor); }
;
    if (_this->speccolor._refCount == 1) { sjf_color_destroy(&_this->speccolor); }
;
}

void sjf_light_heap(sjs_light* _this) {
}

void sjf_list_heap_iface_animation(sjs_list_heap_iface_animation* _this) {
}

void sjf_list_heap_iface_animation_copy(sjs_list_heap_iface_animation* _this, sjs_list_heap_iface_animation* _from) {
    _this->array._refCount = 1;
#line 1 "lib/common/list.sj"
    sjf_array_heap_iface_animation_copy(&_this->array, &_from->array);
}

void sjf_list_heap_iface_animation_destroy(sjs_list_heap_iface_animation* _this) {
    if (_this->array._refCount == 1) { sjf_array_heap_iface_animation_destroy(&_this->array); }
;
}

void sjf_list_heap_iface_animation_getat_heap(sjs_list_heap_iface_animation* _parent, int32_t index, sji_animation* _return) {
    int32_t sjt_functionParam483;
    sjs_array_heap_iface_animation* sjt_parent188 = 0;

#line 7 "lib/common/array.sj"
    sjt_parent188 = &_parent->array;
#line 8 "lib/common/list.sj"
    sjt_functionParam483 = index;
#line 8
    sjf_array_heap_iface_animation_getat_heap(sjt_parent188, sjt_functionParam483, _return);
}

void sjf_list_heap_iface_animation_getcount(sjs_list_heap_iface_animation* _parent, int32_t* _return) {
#line 4 "lib/common/list.sj"
    (*_return) = (&_parent->array)->count;
}

void sjf_list_heap_iface_animation_heap(sjs_list_heap_iface_animation* _this) {
}

void sjf_list_heap_iface_animation_removeat(sjs_list_heap_iface_animation* _parent, int32_t index) {
#line 55 "lib/common/list.sj"
    if (index < 0 || index >= _parent->array.count) {
#line 56
        halt("removeAt: out of bounds %d:%d\n", index, _parent->array.count);
#line 57
    }
#line 58
    sji_animation* p = (sji_animation*)_parent->array.data;
#line 59
    if (p[index]._parent != 0) {
    p[index]._parent->_refCount--;
    if (p[index]._parent->_refCount <= 0) {
        p[index]._vtbl->destroy(p[index]._parent);
        free(p[index]._parent);
    }
}
;
#line 60
    if (index != _parent->array.count - 1) {
#line 61
        memcpy(p + index, p + index + 1, (_parent->array.count - index - 1) * sizeof(sji_animation));
#line 62
    }
#line 63
    _parent->array.count--;
}

void sjf_list_heap_iface_model(sjs_list_heap_iface_model* _this) {
}

void sjf_list_heap_iface_model_copy(sjs_list_heap_iface_model* _this, sjs_list_heap_iface_model* _from) {
    _this->array._refCount = 1;
#line 1 "lib/common/list.sj"
    sjf_array_heap_iface_model_copy(&_this->array, &_from->array);
}

void sjf_list_heap_iface_model_destroy(sjs_list_heap_iface_model* _this) {
    if (_this->array._refCount == 1) { sjf_array_heap_iface_model_destroy(&_this->array); }
;
}

void sjf_list_heap_iface_model_heap(sjs_list_heap_iface_model* _this) {
}

void sjf_list_rect(sjs_list_rect* _this) {
}

void sjf_list_rect_add(sjs_list_rect* _parent, sjs_rect* item) {
    sjs_array_rect sjt_funcold6 = { -1 };
    int32_t sjt_functionParam516;
    sjs_rect* sjt_functionParam517 = 0;
    sjs_array_rect* sjt_parent208 = 0;

    if ((&_parent->array)->count >= (&_parent->array)->datasize) {
        int32_t sjt_functionParam513;
        int32_t sjt_functionParam514;
        int32_t sjt_functionParam515;
        sjs_array_rect* sjt_parent207 = 0;

        sjt_funcold6._refCount = 1;
#line 134 "lib/common/array.sj"
        sjf_array_rect_copy(&sjt_funcold6, &_parent->array);
#line 134
        sjt_parent207 = &_parent->array;
#line 46 "lib/common/list.sj"
        sjt_functionParam514 = 10;
#line 46
        sjt_functionParam515 = (&_parent->array)->datasize * 2;
#line 46
        sjf_i32_max(sjt_functionParam514, sjt_functionParam515, &sjt_functionParam513);
#line 46
        sjf_array_rect_grow(sjt_parent207, sjt_functionParam513, &sjt_funcold6);
#line 46
        if (_parent->array._refCount == 1) { sjf_array_rect_destroy(&_parent->array); }
;
#line 134 "lib/common/array.sj"
        sjf_array_rect_copy(&_parent->array, &sjt_funcold6);
    }

#line 34 "lib/common/array.sj"
    sjt_parent208 = &_parent->array;
#line 50 "lib/common/list.sj"
    sjt_functionParam516 = (&_parent->array)->count;
#line 44
    sjt_functionParam517 = item;
#line 44
    sjf_array_rect_initat(sjt_parent208, sjt_functionParam516, sjt_functionParam517);

    if (sjt_funcold6._refCount == 1) { sjf_array_rect_destroy(&sjt_funcold6); }
;
}

void sjf_list_rect_copy(sjs_list_rect* _this, sjs_list_rect* _from) {
    _this->array._refCount = 1;
#line 1 "lib/common/list.sj"
    sjf_array_rect_copy(&_this->array, &_from->array);
}

void sjf_list_rect_destroy(sjs_list_rect* _this) {
    if (_this->array._refCount == 1) { sjf_array_rect_destroy(&_this->array); }
;
}

void sjf_list_rect_getat(sjs_list_rect* _parent, int32_t index, sjs_rect* _return) {
    int32_t sjt_functionParam522;
    sjs_array_rect* sjt_parent215 = 0;

#line 7 "lib/common/array.sj"
    sjt_parent215 = &_parent->array;
#line 8 "lib/common/list.sj"
    sjt_functionParam522 = index;
#line 8
    sjf_array_rect_getat(sjt_parent215, sjt_functionParam522, _return);
}

void sjf_list_rect_getat_heap(sjs_list_rect* _parent, int32_t index, sjs_rect** _return) {
    int32_t sjt_functionParam523;
    sjs_array_rect* sjt_parent216 = 0;

#line 7 "lib/common/array.sj"
    sjt_parent216 = &_parent->array;
#line 8 "lib/common/list.sj"
    sjt_functionParam523 = index;
#line 8
    sjf_array_rect_getat_heap(sjt_parent216, sjt_functionParam523, _return);
}

void sjf_list_rect_getcount(sjs_list_rect* _parent, int32_t* _return) {
#line 4 "lib/common/list.sj"
    (*_return) = (&_parent->array)->count;
}

void sjf_list_rect_heap(sjs_list_rect* _this) {
}

void sjf_list_rect_removeat(sjs_list_rect* _parent, int32_t index) {
#line 55 "lib/common/list.sj"
    if (index < 0 || index >= _parent->array.count) {
#line 56
        halt("removeAt: out of bounds %d:%d\n", index, _parent->array.count);
#line 57
    }
#line 58
    sjs_rect* p = (sjs_rect*)_parent->array.data;
#line 59
    ;
#line 60
    if (index != _parent->array.count - 1) {
#line 61
        memcpy(p + index, p + index + 1, (_parent->array.count - index - 1) * sizeof(sjs_rect));
#line 62
    }
#line 63
    _parent->array.count--;
}

void sjf_list_u32(sjs_list_u32* _this) {
}

void sjf_list_u32_copy(sjs_list_u32* _this, sjs_list_u32* _from) {
    _this->array._refCount = 1;
#line 1 "lib/common/list.sj"
    sjf_array_u32_copy(&_this->array, &_from->array);
}

void sjf_list_u32_destroy(sjs_list_u32* _this) {
    if (_this->array._refCount == 1) { sjf_array_u32_destroy(&_this->array); }
;
}

void sjf_list_u32_heap(sjs_list_u32* _this) {
}

void sjf_log(sjs_log* _this) {
}

void sjf_log_copy(sjs_log* _this, sjs_log* _from) {
#line 13 "lib/common/log.sj"
    _this->minlevel = _from->minlevel;
#line 13
    sjs_hash_type_bool* copyoption2 = (_from->traceincludes._refCount != -1 ? &_from->traceincludes : 0);
    if (copyoption2 != 0) {
        _this->traceincludes._refCount = 1;
#line 13 "lib/common/log.sj"
        sjf_hash_type_bool_copy(&_this->traceincludes, copyoption2);
    } else {
        _this->traceincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption3 = (_from->debugincludes._refCount != -1 ? &_from->debugincludes : 0);
    if (copyoption3 != 0) {
        _this->debugincludes._refCount = 1;
#line 13 "lib/common/log.sj"
        sjf_hash_type_bool_copy(&_this->debugincludes, copyoption3);
    } else {
        _this->debugincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption4 = (_from->infoincludes._refCount != -1 ? &_from->infoincludes : 0);
    if (copyoption4 != 0) {
        _this->infoincludes._refCount = 1;
#line 13 "lib/common/log.sj"
        sjf_hash_type_bool_copy(&_this->infoincludes, copyoption4);
    } else {
        _this->infoincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption5 = (_from->warnincludes._refCount != -1 ? &_from->warnincludes : 0);
    if (copyoption5 != 0) {
        _this->warnincludes._refCount = 1;
#line 13 "lib/common/log.sj"
        sjf_hash_type_bool_copy(&_this->warnincludes, copyoption5);
    } else {
        _this->warnincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption6 = (_from->errorincludes._refCount != -1 ? &_from->errorincludes : 0);
    if (copyoption6 != 0) {
        _this->errorincludes._refCount = 1;
#line 13 "lib/common/log.sj"
        sjf_hash_type_bool_copy(&_this->errorincludes, copyoption6);
    } else {
        _this->errorincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption7 = (_from->fatalincludes._refCount != -1 ? &_from->fatalincludes : 0);
    if (copyoption7 != 0) {
        _this->fatalincludes._refCount = 1;
#line 13 "lib/common/log.sj"
        sjf_hash_type_bool_copy(&_this->fatalincludes, copyoption7);
    } else {
        _this->fatalincludes._refCount = -1;
    }
}

void sjf_log_destroy(sjs_log* _this) {
    if (_this->traceincludes._refCount == 1) { sjf_hash_type_bool_destroy(&_this->traceincludes); }
;
    if (_this->debugincludes._refCount == 1) { sjf_hash_type_bool_destroy(&_this->debugincludes); }
;
    if (_this->infoincludes._refCount == 1) { sjf_hash_type_bool_destroy(&_this->infoincludes); }
;
    if (_this->warnincludes._refCount == 1) { sjf_hash_type_bool_destroy(&_this->warnincludes); }
;
    if (_this->errorincludes._refCount == 1) { sjf_hash_type_bool_destroy(&_this->errorincludes); }
;
    if (_this->fatalincludes._refCount == 1) { sjf_hash_type_bool_destroy(&_this->fatalincludes); }
;
}

void sjf_log_heap(sjs_log* _this) {
}

void sjf_mainloop(void) {
    int32_option mouse_eventtype;
    bool mouse_isleftdown;
    int32_t mouse_x;
    int32_t mouse_y;
    sjs_rect rect = { -1 };
    bool result39;
    bool shouldappcontinue;
    bool shouldcontinue;
    sjs_size size = { -1 };
    sjs_string sjt_call27 = { -1 };
    sjs_string sjt_call28 = { -1 };
    sjs_string sjt_call29 = { -1 };
    bool sjt_capture140;
    int32_t sjt_functionParam486;
    sjs_size* sjt_functionParam512 = 0;
    sjs_rect* sjt_functionParam521 = 0;
    sjs_scene2d* sjt_interfaceParam3 = 0;
    sjs_animator* sjt_parent192 = 0;
    sjs_windowrenderer* sjt_parent204 = 0;
    sjs_scene2d* sjt_parent206 = 0;
    sjs_scene2d* sjt_parent210 = 0;
    sjs_rect* sjt_parent211 = 0;
    sji_element sjt_parent213 = { 0 };
    sjs_scene2d* sjt_parent225 = 0;
    sjs_windowrenderer* sjt_parent226 = 0;
    int32_t ticks;

#line 9 "lib/ui/loop.sj"
    shouldappcontinue = true;
#line 10
    ticks = 0;
#line 12
    ticks = SDL_GetTicks();
#line 31 "lib/ui/animation.sj"
    sjt_parent192 = &g_animator;
#line 14 "lib/ui/loop.sj"
    sjt_functionParam486 = ticks;
#line 14
    sjf_animator_nextframe(sjt_parent192, sjt_functionParam486);
    if (g_mainloop_showfps) {
#line 17 "lib/ui/loop.sj"
        g_mainloop_frames = g_mainloop_frames + 1;
        if ((g_mainloop_lasttick + 1000) < ticks) {
            float fps;
            int32_t sjt_cast18;
            int32_t sjt_cast19;
            sjs_string* sjt_functionParam490 = 0;
            sjs_string* sjt_functionParam500 = 0;
            float sjt_functionParam501;
            sjs_string* sjt_parent203 = 0;

#line 19 "lib/ui/loop.sj"
            sjt_cast18 = g_mainloop_frames;
#line 19
            sjt_cast19 = ticks - g_mainloop_lasttick;
#line 19
            fps = ((float)sjt_cast18 * 1000.0f) / (float)sjt_cast19;
#line 19
            sjt_call28._refCount = 1;
#line 20
            sjt_call28.count = 5;
#line 20
            sjt_call28.data._refCount = 1;
#line 20
            sjt_call28.data.datasize = 5;
#line 20
            sjt_call28.data.data = (void*)sjg_string16;
#line 20
            sjt_call28.data.isglobal = true;
#line 20
            sjt_call28.data.count = 5;
#line 20
            sjf_array_char(&sjt_call28.data);
#line 14 "lib/common/string.sj"
            sjt_call28._isnullterminated = false;
#line 14
            sjf_string(&sjt_call28);
#line 20 "lib/ui/loop.sj"
            sjt_parent203 = &sjt_call28;
#line 20
            sjt_functionParam501 = fps;
#line 20
            sjf_f32_asstring(sjt_functionParam501, &sjt_call29);
#line 20
            sjt_functionParam500 = &sjt_call29;
#line 20
            sjf_string_add(sjt_parent203, sjt_functionParam500, &sjt_call27);
#line 20
            sjt_functionParam490 = &sjt_call27;
#line 20
            sjf_debug_writeline(sjt_functionParam490);
#line 21
            g_mainloop_lasttick = ticks;
#line 22
            g_mainloop_frames = 0;
        }
    }

#line 7 "lib/ui/windowRenderer.sj"
    sjt_parent204 = &g_rootwindowrenderer;
#line 7
    sjf_windowrenderer_getsize(sjt_parent204, &size);
#line 27 "lib/ui/scene2d.sj"
    sjt_parent206 = &g_rootscene;
#line 27 "lib/ui/loop.sj"
    sjt_functionParam512 = &size;
#line 27
    sjf_scene2d_setsize(sjt_parent206, sjt_functionParam512);
#line 8 "lib/ui/scene2d.sj"
    sjt_parent210 = &g_rootscene;
#line 8
    sjf_scene2d_start(sjt_parent210);
#line 8
    rect._refCount = 1;
#line 29 "lib/ui/loop.sj"
    rect.x = 0;
#line 29
    rect.y = 0;
#line 29
    rect.w = (&size)->w;
#line 29
    rect.h = (&size)->h;
#line 29
    sjf_rect(&rect);
#line 15 "lib/ui/rect.sj"
    sjt_parent211 = &g_looplastrect;
#line 30 "lib/ui/loop.sj"
    sjt_functionParam521 = &rect;
#line 30
    sjf_rect_isequal(sjt_parent211, sjt_functionParam521, &sjt_capture140);
#line 30
    result39 = !sjt_capture140;
    if (result39) {
        sjs_rect* sjt_interfaceParam2 = 0;
        sji_element sjt_parent212 = { 0 };

#line 4 "lib/ui/element.sj"
        sjt_parent212 = g_root;
#line 31 "lib/ui/loop.sj"
        sjt_interfaceParam2 = &rect;
#line 31
        sjt_parent212._vtbl->setrect(sjt_parent212._parent, sjt_interfaceParam2);
    }

#line 5 "lib/ui/element.sj"
    sjt_parent213 = g_root;
#line 33 "lib/ui/loop.sj"
    sjt_interfaceParam3 = &g_rootscene;
#line 33
    sjt_parent213._vtbl->render(sjt_parent213._parent, sjt_interfaceParam3);
#line 19 "lib/ui/scene2d.sj"
    sjt_parent225 = &g_rootscene;
#line 19
    sjf_scene2d_end(sjt_parent225);
#line 22 "lib/ui/windowRenderer.sj"
    sjt_parent226 = &g_rootwindowrenderer;
#line 22
    sjf_windowrenderer_present(sjt_parent226);
#line 38 "lib/ui/loop.sj"
    SDL_Event e;
#line 39
    while(SDL_PollEvent( &e ) != 0) {
#line 41
        mouse_eventtype = int32_empty;
#line 42
        mouse_x = 0;
#line 43
        mouse_y = 0;
#line 44
        mouse_isleftdown = false;
#line 47
        switch (e.type) {
#line 48
            case SDL_QUIT:
#line 49
            shouldappcontinue = false;
#line 50
            break;
#line 51
            case SDL_MOUSEBUTTONDOWN:
#line 52
            mouse_eventtype.isvalid = true;
#line 53
            mouse_eventtype.value = g_mouseeventtype_down;
#line 54
            mouse_x = e.button.x;
#line 55
            mouse_y = e.button.y;
#line 56
            mouse_isleftdown = e.button.state & SDL_BUTTON(SDL_BUTTON_LEFT);
#line 57
            break;
#line 58
            case SDL_MOUSEBUTTONUP:
#line 59
            mouse_eventtype.isvalid = true;
#line 60
            mouse_eventtype.value = g_mouseeventtype_up;
#line 61
            mouse_x = e.button.x;
#line 62
            mouse_y = e.button.y;
#line 63
            mouse_isleftdown = e.button.state & SDL_BUTTON(SDL_BUTTON_LEFT);
#line 64
            break;
#line 65
            case SDL_MOUSEMOTION:
#line 66
            mouse_eventtype.isvalid = true;
#line 67
            mouse_eventtype.value = g_mouseeventtype_move;
#line 68
            mouse_x = e.motion.x;
#line 69
            mouse_y = e.motion.y;
#line 70
            mouse_isleftdown = SDL_GetGlobalMouseState(0, 0) & SDL_BUTTON(SDL_BUTTON_LEFT);
#line 71
            break;
#line 72
        }
#line 75
        shouldcontinue = true;
        if (mouse_eventtype.isvalid) {
            int32_t ifValue1;
            int32_option sjt_getValue1;

#line 76 "lib/ui/loop.sj"
            sjt_getValue1 = mouse_eventtype;
#line 76
            ifValue1 = sjt_getValue1.value;
            if ((g_mouse_captureelement._parent != 0)) {
                sji_element ifValue2 = { 0 };
                sjs_mouseevent sjt_call32 = { -1 };
                bool sjt_funcold7;
                sjs_mouseevent* sjt_interfaceParam4 = 0;
                sji_element sjt_parent227 = { 0 };

#line 77 "lib/ui/loop.sj"
                ifValue2 = g_mouse_captureelement;
                if (ifValue2._parent != 0) {
                    ifValue2._parent->_refCount++;
                }

#line 6 "lib/ui/element.sj"
                sjt_parent227 = ifValue2;
#line 6
                sjt_funcold7 = shouldcontinue;
#line 6
                sjt_call32._refCount = 1;
#line 78 "lib/ui/loop.sj"
                sjt_call32.eventtype = ifValue1;
#line 78
                sjt_call32.point._refCount = 1;
#line 80
                sjt_call32.point.x = mouse_x;
#line 80
                sjt_call32.point.y = mouse_y;
#line 80
                sjf_point(&sjt_call32.point);
#line 81
                sjt_call32.iscaptured = true;
#line 78
                sjt_call32.isleftdown = mouse_isleftdown;
#line 78
                sjf_mouseevent(&sjt_call32);
#line 78
                sjt_interfaceParam4 = &sjt_call32;
#line 78
                sjt_parent227._vtbl->firemouseevent(sjt_parent227._parent, sjt_interfaceParam4, &sjt_funcold7);
#line 6 "lib/ui/element.sj"
                shouldcontinue = sjt_funcold7;

                if (ifValue2._parent != 0) {
                    ifValue2._parent->_refCount--;
                    if (ifValue2._parent->_refCount <= 0) {
                        ifValue2._vtbl->destroy(ifValue2._parent);
                        free(ifValue2._parent);
                    }
                }
                if (sjt_call32._refCount == 1) { sjf_mouseevent_destroy(&sjt_call32); }
;
            } else {
                sjs_mouseevent sjt_call33 = { -1 };
                bool sjt_funcold8;
                sjs_mouseevent* sjt_interfaceParam5 = 0;
                sji_element sjt_parent228 = { 0 };

#line 6 "lib/ui/element.sj"
                sjt_parent228 = g_root;
#line 6
                sjt_funcold8 = shouldcontinue;
#line 6
                sjt_call33._refCount = 1;
#line 86 "lib/ui/loop.sj"
                sjt_call33.eventtype = ifValue1;
#line 86
                sjt_call33.point._refCount = 1;
#line 88
                sjt_call33.point.x = mouse_x;
#line 88
                sjt_call33.point.y = mouse_y;
#line 88
                sjf_point(&sjt_call33.point);
#line 89
                sjt_call33.iscaptured = false;
#line 86
                sjt_call33.isleftdown = mouse_isleftdown;
#line 86
                sjf_mouseevent(&sjt_call33);
#line 86
                sjt_interfaceParam5 = &sjt_call33;
#line 86
                sjt_parent228._vtbl->firemouseevent(sjt_parent228._parent, sjt_interfaceParam5, &sjt_funcold8);
#line 6 "lib/ui/element.sj"
                shouldcontinue = sjt_funcold8;

                if (sjt_call33._refCount == 1) { sjf_mouseevent_destroy(&sjt_call33); }
;
            }
        }

#line 96
    }
#line 99
    g_mainloop_shouldcontinue = shouldappcontinue;

    if (rect._refCount == 1) { sjf_rect_destroy(&rect); }
;
    if (size._refCount == 1) { sjf_size_destroy(&size); }
;
    if (sjt_call27._refCount == 1) { sjf_string_destroy(&sjt_call27); }
;
    if (sjt_call28._refCount == 1) { sjf_string_destroy(&sjt_call28); }
;
    if (sjt_call29._refCount == 1) { sjf_string_destroy(&sjt_call29); }
;
}

void sjf_mat4(sjs_mat4* _this) {
}

void sjf_mat4_copy(sjs_mat4* _this, sjs_mat4* _from) {
#line 1 "lib/ui/mat4.sj"
    _this->m00 = _from->m00;
#line 1
    _this->m01 = _from->m01;
#line 1
    _this->m02 = _from->m02;
#line 1
    _this->m03 = _from->m03;
#line 1
    _this->m10 = _from->m10;
#line 1
    _this->m11 = _from->m11;
#line 1
    _this->m12 = _from->m12;
#line 1
    _this->m13 = _from->m13;
#line 1
    _this->m20 = _from->m20;
#line 1
    _this->m21 = _from->m21;
#line 1
    _this->m22 = _from->m22;
#line 1
    _this->m23 = _from->m23;
#line 1
    _this->m30 = _from->m30;
#line 1
    _this->m31 = _from->m31;
#line 1
    _this->m32 = _from->m32;
#line 1
    _this->m33 = _from->m33;
}

void sjf_mat4_destroy(sjs_mat4* _this) {
}

void sjf_mat4_heap(sjs_mat4* _this) {
}

void sjf_mat4_identity(sjs_mat4* _return) {
    _return->_refCount = 1;
#line 126 "lib/ui/mat4.sj"
    _return->m00 = 1.0f;
#line 3
    _return->m01 = 0.0f;
#line 4
    _return->m02 = 0.0f;
#line 5
    _return->m03 = 0.0f;
#line 6
    _return->m10 = 0.0f;
#line 127
    _return->m11 = 1.0f;
#line 8
    _return->m12 = 0.0f;
#line 9
    _return->m13 = 0.0f;
#line 10
    _return->m20 = 0.0f;
#line 11
    _return->m21 = 0.0f;
#line 128
    _return->m22 = 1.0f;
#line 13
    _return->m23 = 0.0f;
#line 14
    _return->m30 = 0.0f;
#line 15
    _return->m31 = 0.0f;
#line 16
    _return->m32 = 0.0f;
#line 129
    _return->m33 = 1.0f;
#line 129
    sjf_mat4(_return);
}

void sjf_mat4_identity_heap(sjs_mat4** _return) {
    (*_return) = (sjs_mat4*)malloc(sizeof(sjs_mat4));
    (*_return)->_refCount = 1;
#line 126 "lib/ui/mat4.sj"
    (*_return)->m00 = 1.0f;
#line 3
    (*_return)->m01 = 0.0f;
#line 4
    (*_return)->m02 = 0.0f;
#line 5
    (*_return)->m03 = 0.0f;
#line 6
    (*_return)->m10 = 0.0f;
#line 127
    (*_return)->m11 = 1.0f;
#line 8
    (*_return)->m12 = 0.0f;
#line 9
    (*_return)->m13 = 0.0f;
#line 10
    (*_return)->m20 = 0.0f;
#line 11
    (*_return)->m21 = 0.0f;
#line 128
    (*_return)->m22 = 1.0f;
#line 13
    (*_return)->m23 = 0.0f;
#line 14
    (*_return)->m30 = 0.0f;
#line 15
    (*_return)->m31 = 0.0f;
#line 16
    (*_return)->m32 = 0.0f;
#line 129
    (*_return)->m33 = 1.0f;
#line 129
    sjf_mat4_heap((*_return));
}

void sjf_mat4_orthographic(float left, float right, float bottom, float top, float znear, float zfar, sjs_mat4* _return) {
    float result35;

    _return->_refCount = 1;
#line 172 "lib/ui/mat4.sj"
    _return->m00 = 2.0f / (right - left);
#line 3
    _return->m01 = 0.0f;
#line 4
    _return->m02 = 0.0f;
#line 5
    _return->m03 = 0.0f;
#line 6
    _return->m10 = 0.0f;
#line 174
    _return->m11 = 2.0f / (top - bottom);
#line 8
    _return->m12 = 0.0f;
#line 9
    _return->m13 = 0.0f;
#line 10
    _return->m20 = 0.0f;
#line 11
    _return->m21 = 0.0f;
#line 176
    result35 = -2.0f;
#line 176
    _return->m22 = result35 / (zfar - znear);
#line 13
    _return->m23 = 0.0f;
#line 173
    _return->m30 = 0.0f - ((right + left) / (right - left));
#line 175
    _return->m31 = 0.0f - ((top + bottom) / (top - bottom));
#line 177
    _return->m32 = 0.0f - ((zfar + znear) / (zfar - znear));
#line 178
    _return->m33 = 1.0f;
#line 178
    sjf_mat4(_return);
}

void sjf_mat4_orthographic_heap(float left, float right, float bottom, float top, float znear, float zfar, sjs_mat4** _return) {
    float result36;

    (*_return) = (sjs_mat4*)malloc(sizeof(sjs_mat4));
    (*_return)->_refCount = 1;
#line 172 "lib/ui/mat4.sj"
    (*_return)->m00 = 2.0f / (right - left);
#line 3
    (*_return)->m01 = 0.0f;
#line 4
    (*_return)->m02 = 0.0f;
#line 5
    (*_return)->m03 = 0.0f;
#line 6
    (*_return)->m10 = 0.0f;
#line 174
    (*_return)->m11 = 2.0f / (top - bottom);
#line 8
    (*_return)->m12 = 0.0f;
#line 9
    (*_return)->m13 = 0.0f;
#line 10
    (*_return)->m20 = 0.0f;
#line 11
    (*_return)->m21 = 0.0f;
#line 176
    result36 = -2.0f;
#line 176
    (*_return)->m22 = result36 / (zfar - znear);
#line 13
    (*_return)->m23 = 0.0f;
#line 173
    (*_return)->m30 = 0.0f - ((right + left) / (right - left));
#line 175
    (*_return)->m31 = 0.0f - ((top + bottom) / (top - bottom));
#line 177
    (*_return)->m32 = 0.0f - ((zfar + znear) / (zfar - znear));
#line 178
    (*_return)->m33 = 1.0f;
#line 178
    sjf_mat4_heap((*_return));
}

void sjf_mat4_scale(float x, float y, float z, sjs_mat4* _return) {
    _return->_refCount = 1;
#line 213 "lib/ui/mat4.sj"
    _return->m00 = x;
#line 3
    _return->m01 = 0.0f;
#line 4
    _return->m02 = 0.0f;
#line 5
    _return->m03 = 0.0f;
#line 6
    _return->m10 = 0.0f;
#line 213
    _return->m11 = y;
#line 8
    _return->m12 = 0.0f;
#line 9
    _return->m13 = 0.0f;
#line 10
    _return->m20 = 0.0f;
#line 11
    _return->m21 = 0.0f;
#line 213
    _return->m22 = z;
#line 13
    _return->m23 = 0.0f;
#line 14
    _return->m30 = 0.0f;
#line 15
    _return->m31 = 0.0f;
#line 16
    _return->m32 = 0.0f;
#line 218
    _return->m33 = 1.0f;
#line 218
    sjf_mat4(_return);
}

void sjf_mat4_scale_heap(float x, float y, float z, sjs_mat4** _return) {
    (*_return) = (sjs_mat4*)malloc(sizeof(sjs_mat4));
    (*_return)->_refCount = 1;
#line 213 "lib/ui/mat4.sj"
    (*_return)->m00 = x;
#line 3
    (*_return)->m01 = 0.0f;
#line 4
    (*_return)->m02 = 0.0f;
#line 5
    (*_return)->m03 = 0.0f;
#line 6
    (*_return)->m10 = 0.0f;
#line 213
    (*_return)->m11 = y;
#line 8
    (*_return)->m12 = 0.0f;
#line 9
    (*_return)->m13 = 0.0f;
#line 10
    (*_return)->m20 = 0.0f;
#line 11
    (*_return)->m21 = 0.0f;
#line 213
    (*_return)->m22 = z;
#line 13
    (*_return)->m23 = 0.0f;
#line 14
    (*_return)->m30 = 0.0f;
#line 15
    (*_return)->m31 = 0.0f;
#line 16
    (*_return)->m32 = 0.0f;
#line 218
    (*_return)->m33 = 1.0f;
#line 218
    sjf_mat4_heap((*_return));
}

void sjf_mouseevent(sjs_mouseevent* _this) {
}

void sjf_mouseevent_copy(sjs_mouseevent* _this, sjs_mouseevent* _from) {
#line 38 "lib/ui/mouse.sj"
    _this->eventtype = _from->eventtype;
#line 38
    _this->point._refCount = 1;
#line 38
    sjf_point_copy(&_this->point, &_from->point);
#line 38
    _this->iscaptured = _from->iscaptured;
#line 38
    _this->isleftdown = _from->isleftdown;
}

void sjf_mouseevent_destroy(sjs_mouseevent* _this) {
    if (_this->point._refCount == 1) { sjf_point_destroy(&_this->point); }
;
}

void sjf_mouseevent_heap(sjs_mouseevent* _this) {
}

void sjf_point(sjs_point* _this) {
}

void sjf_point_copy(sjs_point* _this, sjs_point* _from) {
#line 1 "lib/ui/point.sj"
    _this->x = _from->x;
#line 1
    _this->y = _from->y;
}

void sjf_point_destroy(sjs_point* _this) {
}

void sjf_point_heap(sjs_point* _this) {
}

void sjf_rect(sjs_rect* _this) {
}

void sjf_rect_copy(sjs_rect* _this, sjs_rect* _from) {
#line 1 "lib/ui/rect.sj"
    _this->x = _from->x;
#line 1
    _this->y = _from->y;
#line 1
    _this->w = _from->w;
#line 1
    _this->h = _from->h;
}

void sjf_rect_destroy(sjs_rect* _this) {
}

void sjf_rect_heap(sjs_rect* _this) {
}

void sjf_rect_isequal(sjs_rect* _parent, sjs_rect* rect, bool* _return) {
    if (_parent->x == rect->x) {
        bool sjt_capture4;

        if (_parent->y == rect->y) {
            bool sjt_capture5;

            if (_parent->w == rect->w) {
#line 16 "lib/ui/rect.sj"
                sjt_capture5 = (_parent->h == rect->h);
            } else {
#line 16 "lib/ui/rect.sj"
                sjt_capture5 = false;
            }

#line 16 "lib/ui/rect.sj"
            sjt_capture4 = sjt_capture5;
        } else {
#line 16 "lib/ui/rect.sj"
            sjt_capture4 = false;
        }

#line 16 "lib/ui/rect.sj"
        (*_return) = sjt_capture4;
    } else {
#line 16 "lib/ui/rect.sj"
        (*_return) = false;
    }
}

void sjf_runloop(void) {
#line 105 "lib/ui/loop.sj"
    #ifdef EMSCRIPTEN
#line 106
    emscripten_set_main_loop((em_callback_func)sjf_mainloop, 0, 0);
#line 107
    exit(0);
#line 108
    #else
#line 109
    while (g_mainloop_shouldcontinue) {
#line 110
        sjf_mainloop();
#line 111
    }
#line 112
    #endif 
}

void sjf_scene2d(sjs_scene2d* _this) {
}

void sjf_scene2d_copy(sjs_scene2d* _this, sjs_scene2d* _from) {
    _this->_size._refCount = 1;
#line 1 "lib/ui/scene2d.sj"
    sjf_size_copy(&_this->_size, &_from->_size);
#line 1
    _this->model._refCount = 1;
#line 1
    sjf_mat4_copy(&_this->model, &_from->model);
#line 1
    _this->view._refCount = 1;
#line 1
    sjf_mat4_copy(&_this->view, &_from->view);
#line 1
    _this->projection._refCount = 1;
#line 1
    sjf_mat4_copy(&_this->projection, &_from->projection);
#line 1
    _this->windowrect._refCount = 1;
#line 1
    sjf_rect_copy(&_this->windowrect, &_from->windowrect);
}

void sjf_scene2d_destroy(sjs_scene2d* _this) {
    if (_this->_size._refCount == 1) { sjf_size_destroy(&_this->_size); }
;
    if (_this->model._refCount == 1) { sjf_mat4_destroy(&_this->model); }
;
    if (_this->view._refCount == 1) { sjf_mat4_destroy(&_this->view); }
;
    if (_this->projection._refCount == 1) { sjf_mat4_destroy(&_this->projection); }
;
    if (_this->windowrect._refCount == 1) { sjf_rect_destroy(&_this->windowrect); }
;
}

void sjf_scene2d_end(sjs_scene2d* _parent) {
    sjs_rect* sjt_functionParam529 = 0;
    sjs_rect* sjt_functionParam530 = 0;

#line 20 "lib/ui/scene2d.sj"
    sjt_functionParam529 = &_parent->windowrect;
#line 20
    sjt_functionParam530 = &_parent->windowrect;
#line 20
    sjf_glpopviewport(sjt_functionParam529, sjt_functionParam530);
}

void sjf_scene2d_heap(sjs_scene2d* _this) {
}

void sjf_scene2d_setsize(sjs_scene2d* _parent, sjs_size* size) {
    bool result34;
    bool sjt_capture139;
    sjs_mat4 sjt_funcold2 = { -1 };
    sjs_mat4 sjt_funcold3 = { -1 };
    sjs_mat4 sjt_funcold4 = { -1 };
    sjs_size* sjt_functionParam502 = 0;
    sjs_size* sjt_parent205 = 0;

#line 27 "lib/ui/size.sj"
    sjt_parent205 = &_parent->_size;
#line 27 "lib/ui/scene2d.sj"
    sjt_functionParam502 = size;
#line 27
    sjf_size_isequal(sjt_parent205, sjt_functionParam502, &sjt_capture139);
#line 28
    result34 = !sjt_capture139;
    if (result34) {
        float result37;
        float result38;
        int32_t sjt_cast20;
        int32_t sjt_cast21;
        float sjt_functionParam503;
        float sjt_functionParam504;
        float sjt_functionParam505;
        float sjt_functionParam506;
        float sjt_functionParam507;
        float sjt_functionParam508;
        float sjt_functionParam509;
        float sjt_functionParam510;
        float sjt_functionParam511;

        if (_parent->_size._refCount == 1) { sjf_size_destroy(&_parent->_size); }
;
#line 27 "lib/ui/scene2d.sj"
        sjf_size_copy(&_parent->_size, size);
#line 27
        sjt_funcold2._refCount = 1;
#line 170 "lib/ui/mat4.sj"
        sjf_mat4_copy(&sjt_funcold2, &_parent->projection);
#line 30 "lib/ui/scene2d.sj"
        sjt_functionParam503 = 0.0f;
#line 30
        sjt_cast20 = (&_parent->_size)->w;
#line 30
        sjt_functionParam504 = (float)sjt_cast20;
#line 30
        sjt_cast21 = 0 - (&_parent->_size)->h;
#line 30
        sjt_functionParam505 = (float)sjt_cast21;
#line 30
        sjt_functionParam506 = 0.0f;
#line 30
        result37 = -1.0f;
#line 30
        sjt_functionParam507 = result37;
#line 30
        sjt_functionParam508 = 1.0f;
#line 30
        sjf_mat4_orthographic(sjt_functionParam503, sjt_functionParam504, sjt_functionParam505, sjt_functionParam506, sjt_functionParam507, sjt_functionParam508, &sjt_funcold2);
#line 30
        if (_parent->projection._refCount == 1) { sjf_mat4_destroy(&_parent->projection); }
;
#line 170 "lib/ui/mat4.sj"
        sjf_mat4_copy(&_parent->projection, &sjt_funcold2);
#line 170
        sjt_funcold3._refCount = 1;
#line 213
        sjf_mat4_copy(&sjt_funcold3, &_parent->model);
#line 31 "lib/ui/scene2d.sj"
        sjt_functionParam509 = 1.0f;
#line 31
        result38 = -1.0f;
#line 31
        sjt_functionParam510 = result38;
#line 31
        sjt_functionParam511 = 1.0f;
#line 31
        sjf_mat4_scale(sjt_functionParam509, sjt_functionParam510, sjt_functionParam511, &sjt_funcold3);
#line 31
        if (_parent->model._refCount == 1) { sjf_mat4_destroy(&_parent->model); }
;
#line 213 "lib/ui/mat4.sj"
        sjf_mat4_copy(&_parent->model, &sjt_funcold3);
#line 213
        sjt_funcold4._refCount = 1;
#line 124
        sjf_mat4_copy(&sjt_funcold4, &_parent->view);
#line 124
        sjf_mat4_identity(&sjt_funcold4);
#line 124
        if (_parent->view._refCount == 1) { sjf_mat4_destroy(&_parent->view); }
;
#line 124
        sjf_mat4_copy(&_parent->view, &sjt_funcold4);
    }

    if (sjt_funcold2._refCount == 1) { sjf_mat4_destroy(&sjt_funcold2); }
;
    if (sjt_funcold3._refCount == 1) { sjf_mat4_destroy(&sjt_funcold3); }
;
    if (sjt_funcold4._refCount == 1) { sjf_mat4_destroy(&sjt_funcold4); }
;
}

void sjf_scene2d_start(sjs_scene2d* _parent) {
    sjs_rect sjt_funcold5 = { -1 };
    sjs_rect* sjt_functionParam519 = 0;
    sjs_rect* sjt_functionParam520 = 0;

    sjt_funcold5._refCount = 1;
#line 1 "lib/ui/rect.sj"
    sjf_rect_copy(&sjt_funcold5, &_parent->windowrect);
#line 1
    sjt_funcold5._refCount = 1;
#line 9 "lib/ui/scene2d.sj"
    sjt_funcold5.x = 0;
#line 9
    sjt_funcold5.y = 0;
#line 9
    sjt_funcold5.w = (&_parent->_size)->w;
#line 9
    sjt_funcold5.h = (&_parent->_size)->h;
#line 9
    sjf_rect(&sjt_funcold5);
#line 9
    if (_parent->windowrect._refCount == 1) { sjf_rect_destroy(&_parent->windowrect); }
;
#line 1 "lib/ui/rect.sj"
    sjf_rect_copy(&_parent->windowrect, &sjt_funcold5);
#line 10 "lib/ui/scene2d.sj"
    sjt_functionParam519 = &_parent->windowrect;
#line 10
    sjt_functionParam520 = &_parent->windowrect;
#line 10
    sjf_glpushviewport(sjt_functionParam519, sjt_functionParam520);
#line 12
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
#line 13
    glEnable( GL_TEXTURE_2D );
#line 14
    glDisable( GL_DEPTH_TEST );

    if (sjt_funcold5._refCount == 1) { sjf_rect_destroy(&sjt_funcold5); }
;
}

void sjf_shader(sjs_shader* _this) {
#line 15 "lib/ui/shader.sj"
    _this->id = shader_load((char*)_this->vertex.data.data, (char*)_this->pixel.data.data);
}

void sjf_shader_copy(sjs_shader* _this, sjs_shader* _from) {
    _this->vertex._refCount = 1;
#line 7 "lib/ui/shader.sj"
    sjf_string_copy(&_this->vertex, &_from->vertex);
#line 7
    _this->pixel._refCount = 1;
#line 7
    sjf_string_copy(&_this->pixel, &_from->pixel);
#line 20
    _this->id = _from->id;
#line 21
    glid_retain(_this->id);
}

void sjf_shader_destroy(sjs_shader* _this) {
#line 25 "lib/ui/shader.sj"
    if (glid_release(_this->id)) {
#line 26
        glDeleteShader(_this->id);
#line 27
    }
#line 27
    if (_this->vertex._refCount == 1) { sjf_string_destroy(&_this->vertex); }
;
#line 27
    if (_this->pixel._refCount == 1) { sjf_string_destroy(&_this->pixel); }
;
}

void sjf_shader_heap(sjs_shader* _this) {
#line 15 "lib/ui/shader.sj"
    _this->id = shader_load((char*)_this->vertex.data.data, (char*)_this->pixel.data.data);
}

void sjf_size(sjs_size* _this) {
}

void sjf_size_copy(sjs_size* _this, sjs_size* _from) {
#line 1 "lib/ui/size.sj"
    _this->w = _from->w;
#line 1
    _this->h = _from->h;
}

void sjf_size_destroy(sjs_size* _this) {
}

void sjf_size_heap(sjs_size* _this) {
}

void sjf_size_isequal(sjs_size* _parent, sjs_size* size, bool* _return) {
    if (_parent->w == size->w) {
#line 28 "lib/ui/size.sj"
        (*_return) = (_parent->h == size->h);
    } else {
#line 28 "lib/ui/size.sj"
        (*_return) = false;
    }
}

void sjf_string(sjs_string* _this) {
}

void sjf_string_add(sjs_string* _parent, sjs_string* item, sjs_string* _return) {
    sjs_array_char newdata = { -1 };

    if (item->count == 0) {
        _return->_refCount = 1;
#line 18 "lib/common/string.sj"
        _return->count = _parent->count;
#line 18
        _return->data._refCount = 1;
#line 18
        sjf_array_char_copy(&_return->data, &_parent->data);
#line 14
        _return->_isnullterminated = false;
#line 14
        sjf_string(_return);
    } else {
        int32_t i;
        int32_t newcount;
        int32_t sjt_forEnd22;
        int32_t sjt_forStart22;

        if ((_parent->count + item->count) > (&_parent->data)->datasize) {
            int32_t sjt_functionParam491;
            sjs_array_char* sjt_parent196 = 0;

#line 134 "lib/common/array.sj"
            sjt_parent196 = &_parent->data;
#line 21 "lib/common/string.sj"
            sjt_functionParam491 = ((((_parent->count + item->count) - 1) / 256) + 1) * 256;
#line 21
            sjf_array_char_grow(sjt_parent196, sjt_functionParam491, &newdata);
        } else {
            newdata._refCount = 1;
#line 20 "lib/common/string.sj"
            sjf_array_char_copy(&newdata, &_parent->data);
        }

#line 25 "lib/common/string.sj"
        newcount = _parent->count;
#line 27
        sjt_forStart22 = 0;
#line 27
        sjt_forEnd22 = item->count;
#line 27
        i = sjt_forStart22;
        while (i < sjt_forEnd22) {
            int32_t sjt_functionParam492;
            char sjt_functionParam493;
            int32_t sjt_functionParam495;
            sjs_array_char* sjt_parent197 = 0;
            sjs_string* sjt_parent199 = 0;

#line 34 "lib/common/array.sj"
            sjt_parent197 = &newdata;
#line 28 "lib/common/string.sj"
            sjt_functionParam492 = newcount;
#line 16
            sjt_parent199 = item;
#line 27
            sjt_functionParam495 = i;
#line 27
            sjf_string_getat(sjt_parent199, sjt_functionParam495, &sjt_functionParam493);
#line 27
            sjf_array_char_initat(sjt_parent197, sjt_functionParam492, sjt_functionParam493);
#line 29
            newcount = newcount + 1;
#line 27
            i++;
        }

#line 27
        _return->_refCount = 1;
#line 32
        _return->count = newcount;
#line 32
        _return->data._refCount = 1;
#line 32
        sjf_array_char_copy(&_return->data, &newdata);
#line 14
        _return->_isnullterminated = false;
#line 14
        sjf_string(_return);
    }

    if (newdata._refCount == 1) { sjf_array_char_destroy(&newdata); }
;
}

void sjf_string_add_heap(sjs_string* _parent, sjs_string* item, sjs_string** _return) {
    sjs_array_char newdata = { -1 };

    if (item->count == 0) {
        (*_return) = (sjs_string*)malloc(sizeof(sjs_string));
        (*_return)->_refCount = 1;
#line 18 "lib/common/string.sj"
        (*_return)->count = _parent->count;
#line 18
        (*_return)->data._refCount = 1;
#line 18
        sjf_array_char_copy(&(*_return)->data, &_parent->data);
#line 14
        (*_return)->_isnullterminated = false;
#line 14
        sjf_string_heap((*_return));
    } else {
        int32_t i;
        int32_t newcount;
        int32_t sjt_forEnd23;
        int32_t sjt_forStart23;

        if ((_parent->count + item->count) > (&_parent->data)->datasize) {
            int32_t sjt_functionParam496;
            sjs_array_char* sjt_parent200 = 0;

#line 134 "lib/common/array.sj"
            sjt_parent200 = &_parent->data;
#line 21 "lib/common/string.sj"
            sjt_functionParam496 = ((((_parent->count + item->count) - 1) / 256) + 1) * 256;
#line 21
            sjf_array_char_grow(sjt_parent200, sjt_functionParam496, &newdata);
        } else {
            newdata._refCount = 1;
#line 20 "lib/common/string.sj"
            sjf_array_char_copy(&newdata, &_parent->data);
        }

#line 25 "lib/common/string.sj"
        newcount = _parent->count;
#line 27
        sjt_forStart23 = 0;
#line 27
        sjt_forEnd23 = item->count;
#line 27
        i = sjt_forStart23;
        while (i < sjt_forEnd23) {
            int32_t sjt_functionParam497;
            char sjt_functionParam498;
            int32_t sjt_functionParam499;
            sjs_array_char* sjt_parent201 = 0;
            sjs_string* sjt_parent202 = 0;

#line 34 "lib/common/array.sj"
            sjt_parent201 = &newdata;
#line 28 "lib/common/string.sj"
            sjt_functionParam497 = newcount;
#line 16
            sjt_parent202 = item;
#line 27
            sjt_functionParam499 = i;
#line 27
            sjf_string_getat(sjt_parent202, sjt_functionParam499, &sjt_functionParam498);
#line 27
            sjf_array_char_initat(sjt_parent201, sjt_functionParam497, sjt_functionParam498);
#line 29
            newcount = newcount + 1;
#line 27
            i++;
        }

#line 27
        (*_return) = (sjs_string*)malloc(sizeof(sjs_string));
#line 27
        (*_return)->_refCount = 1;
#line 32
        (*_return)->count = newcount;
#line 32
        (*_return)->data._refCount = 1;
#line 32
        sjf_array_char_copy(&(*_return)->data, &newdata);
#line 14
        (*_return)->_isnullterminated = false;
#line 14
        sjf_string_heap((*_return));
    }

    if (newdata._refCount == 1) { sjf_array_char_destroy(&newdata); }
;
}

void sjf_string_copy(sjs_string* _this, sjs_string* _from) {
#line 6 "lib/common/string.sj"
    _this->count = _from->count;
#line 6
    _this->data._refCount = 1;
#line 6
    sjf_array_char_copy(&_this->data, &_from->data);
#line 6
    _this->_isnullterminated = _from->_isnullterminated;
}

void sjf_string_destroy(sjs_string* _this) {
    if (_this->data._refCount == 1) { sjf_array_char_destroy(&_this->data); }
;
}

void sjf_string_getat(sjs_string* _parent, int32_t index, char* _return) {
    int32_t sjt_functionParam494;
    sjs_array_char* sjt_parent198 = 0;

#line 7 "lib/common/array.sj"
    sjt_parent198 = &_parent->data;
#line 36 "lib/common/string.sj"
    sjt_functionParam494 = index;
#line 36
    sjf_array_char_getat(sjt_parent198, sjt_functionParam494, _return);
}

void sjf_string_hash(sjs_string* _parent, uint32_t* _return) {
#line 85 "lib/common/string.sj"
    #line 84 "lib/common/string.sj"
(*_return) = kh_str_hash_func((char*)_parent->data.data);
return;;
}

void sjf_string_heap(sjs_string* _this) {
}

void sjf_string_isequal(sjs_string* _parent, sjs_string* test, bool* _return) {
    sjs_array_char* sjt_functionParam9 = 0;
    sjs_array_char* sjt_parent1 = 0;

#line 269 "lib/common/array.sj"
    sjt_parent1 = &_parent->data;
#line 45 "lib/common/string.sj"
    sjt_functionParam9 = &test->data;
#line 45
    sjf_array_char_isequal(sjt_parent1, sjt_functionParam9, _return);
}

void sjf_string_nullterminate(sjs_string* _parent) {
    bool result32;
    bool result33;
    sjs_array_char sjt_funcold1 = { -1 };

#line 73 "lib/common/string.sj"
    result32 = !(&_parent->data)->isglobal;
#line 73
    result33 = !_parent->_isnullterminated;
    if (result32 || result33) {
        int32_t sjt_functionParam488;
        char sjt_functionParam489;
        sjs_array_char* sjt_parent194 = 0;

        if ((_parent->count + 1) > (&_parent->data)->datasize) {
            int32_t sjt_functionParam487;
            sjs_array_char* sjt_parent193 = 0;

            sjt_funcold1._refCount = 1;
#line 134 "lib/common/array.sj"
            sjf_array_char_copy(&sjt_funcold1, &_parent->data);
#line 134
            sjt_parent193 = &_parent->data;
#line 75 "lib/common/string.sj"
            sjt_functionParam487 = _parent->count + 1;
#line 75
            sjf_array_char_grow(sjt_parent193, sjt_functionParam487, &sjt_funcold1);
#line 75
            if (_parent->data._refCount == 1) { sjf_array_char_destroy(&_parent->data); }
;
#line 134 "lib/common/array.sj"
            sjf_array_char_copy(&_parent->data, &sjt_funcold1);
        }

#line 34 "lib/common/array.sj"
        sjt_parent194 = &_parent->data;
#line 77 "lib/common/string.sj"
        sjt_functionParam488 = _parent->count;
#line 77
        sjt_functionParam489 = '\0';
#line 77
        sjf_array_char_initat(sjt_parent194, sjt_functionParam488, sjt_functionParam489);
#line 78
        _parent->_isnullterminated = true;
    }

    if (sjt_funcold1._refCount == 1) { sjf_array_char_destroy(&sjt_funcold1); }
;
}

void sjf_style(sjs_style* _this) {
}

void sjf_style_copy(sjs_style* _this, sjs_style* _from) {
}

void sjf_style_destroy(sjs_style* _this) {
}

void sjf_style_heap(sjs_style* _this) {
}

void sjf_test(sjs_test* _this) {
}

void sjf_test_as_sji_element(sjs_test* _this, sji_element* _return) {
    _return->_parent = (sjs_object*)_this;
    _return->_vtbl = &sjs_test_element_vtbl;
}

void sjf_test_asinterface(sjs_test* _this, int typeId, sjs_interface* _return) {
    switch (typeId) {
        case sji_element_typeId:  {
            sjf_test_as_sji_element(_this, (sji_element*)_return);
            break;
        }

        default: {
            _return->_parent = 0;
            break;
        }
    }
}

void sjf_test_calculate(sjs_test* _parent) {
    int32_t underscore1;

#line 178 "perf2.sj"
    underscore1 = _parent->funcid;
    if (underscore1 == 0) {
        int32_t n;
        int32_t sjt_forEnd1;
        int32_t sjt_forStart1;

#line 180 "perf2.sj"
        sjt_forStart1 = 0;
#line 180
        sjt_forEnd1 = g_dots;
#line 180
        n = sjt_forStart1;
        while (n < sjt_forEnd1) {
            int32_t sjt_functionParam29;
            int32_t sjt_functionParam30;
            int32_t sjt_functionParam31;
            float sjt_functionParam32;
            int32_t sjt_functionParam33;
            float sjt_functionParam34;
            float sjt_functionParam35;
            sjs_array_f32* sjt_parent13 = 0;
            sjs_array_f32* sjt_parent14 = 0;
            float t;

#line 181 "perf2.sj"
            sjt_functionParam29 = 1;
#line 180
            sjt_functionParam30 = n;
#line 180
            sjf_test_gettm(_parent, sjt_functionParam29, sjt_functionParam30, &t);
#line 49 "lib/common/array.sj"
            sjt_parent13 = &_parent->datax;
#line 180 "perf2.sj"
            sjt_functionParam31 = n;
#line 182
            sjt_functionParam32 = t;
#line 182
            sjf_array_f32_setat(sjt_parent13, sjt_functionParam31, sjt_functionParam32);
#line 49 "lib/common/array.sj"
            sjt_parent14 = &_parent->datay;
#line 180 "perf2.sj"
            sjt_functionParam33 = n;
#line 183
            sjt_functionParam35 = t;
#line 183
            sjf_f32_tan(sjt_functionParam35, &sjt_functionParam34);
#line 183
            sjf_array_f32_setat(sjt_parent14, sjt_functionParam33, sjt_functionParam34);
#line 180
            n++;
        }
    } else {
        if (underscore1 == 1) {
            int32_t n;
            int32_t sjt_forEnd2;
            int32_t sjt_forStart2;

#line 187 "perf2.sj"
            sjt_forStart2 = 0;
#line 187
            sjt_forEnd2 = g_dots;
#line 187
            n = sjt_forStart2;
            while (n < sjt_forEnd2) {
                int32_t sjt_functionParam36;
                int32_t sjt_functionParam37;
                int32_t sjt_functionParam38;
                float sjt_functionParam39;
                int32_t sjt_functionParam40;
                float sjt_functionParam41;
                sjs_array_f32* sjt_parent15 = 0;
                sjs_array_f32* sjt_parent16 = 0;
                float t;

#line 188 "perf2.sj"
                sjt_functionParam36 = 1;
#line 187
                sjt_functionParam37 = n;
#line 187
                sjf_test_gettm(_parent, sjt_functionParam36, sjt_functionParam37, &t);
#line 49 "lib/common/array.sj"
                sjt_parent15 = &_parent->datax;
#line 187 "perf2.sj"
                sjt_functionParam38 = n;
#line 189
                sjt_functionParam39 = t;
#line 189
                sjf_array_f32_setat(sjt_parent15, sjt_functionParam38, sjt_functionParam39);
#line 49 "lib/common/array.sj"
                sjt_parent16 = &_parent->datay;
#line 187 "perf2.sj"
                sjt_functionParam40 = n;
#line 190
                sjt_functionParam41 = (t * t) * t;
#line 190
                sjf_array_f32_setat(sjt_parent16, sjt_functionParam40, sjt_functionParam41);
#line 187
                n++;
            }
        } else {
            if (underscore1 == 2) {
                int32_t n;
                int32_t sjt_forEnd3;
                int32_t sjt_forStart3;

#line 194 "perf2.sj"
                sjt_forStart3 = 0;
#line 194
                sjt_forEnd3 = g_dots;
#line 194
                n = sjt_forStart3;
                while (n < sjt_forEnd3) {
                    float sjt_capture7;
                    int32_t sjt_functionParam42;
                    int32_t sjt_functionParam43;
                    int32_t sjt_functionParam44;
                    float sjt_functionParam45;
                    int32_t sjt_functionParam46;
                    float sjt_functionParam47;
                    float sjt_functionParam48;
                    sjs_array_f32* sjt_parent17 = 0;
                    sjs_array_f32* sjt_parent18 = 0;
                    float t;

#line 195 "perf2.sj"
                    sjt_functionParam42 = 2;
#line 194
                    sjt_functionParam43 = n;
#line 194
                    sjf_test_gettm(_parent, sjt_functionParam42, sjt_functionParam43, &t);
#line 49 "lib/common/array.sj"
                    sjt_parent17 = &_parent->datax;
#line 194 "perf2.sj"
                    sjt_functionParam44 = n;
#line 196
                    sjt_functionParam45 = t;
#line 196
                    sjf_array_f32_setat(sjt_parent17, sjt_functionParam44, sjt_functionParam45);
#line 49 "lib/common/array.sj"
                    sjt_parent18 = &_parent->datay;
#line 194 "perf2.sj"
                    sjt_functionParam46 = n;
#line 197
                    sjt_functionParam48 = t;
#line 197
                    sjf_f32_sin(sjt_functionParam48, &sjt_capture7);
#line 197
                    sjt_functionParam47 = (6.0f * sjt_capture7) / 2.0f;
#line 197
                    sjf_array_f32_setat(sjt_parent18, sjt_functionParam46, sjt_functionParam47);
#line 194
                    n++;
                }
            } else {
                if (underscore1 == 3) {
                    int32_t n;
                    int32_t sjt_forEnd4;
                    int32_t sjt_forStart4;

#line 202 "perf2.sj"
                    sjt_forStart4 = 0;
#line 202
                    sjt_forEnd4 = g_dots;
#line 202
                    n = sjt_forStart4;
                    while (n < sjt_forEnd4) {
                        float sjt_capture8;
                        int32_t sjt_functionParam49;
                        int32_t sjt_functionParam50;
                        int32_t sjt_functionParam51;
                        float sjt_functionParam52;
                        int32_t sjt_functionParam53;
                        float sjt_functionParam54;
                        float sjt_functionParam55;
                        sjs_array_f32* sjt_parent19 = 0;
                        sjs_array_f32* sjt_parent20 = 0;
                        float t;

#line 203 "perf2.sj"
                        sjt_functionParam49 = 1;
#line 202
                        sjt_functionParam50 = n;
#line 202
                        sjf_test_gettm(_parent, sjt_functionParam49, sjt_functionParam50, &t);
#line 49 "lib/common/array.sj"
                        sjt_parent19 = &_parent->datax;
#line 202 "perf2.sj"
                        sjt_functionParam51 = n;
#line 204
                        sjt_functionParam52 = t;
#line 204
                        sjf_array_f32_setat(sjt_parent19, sjt_functionParam51, sjt_functionParam52);
#line 49 "lib/common/array.sj"
                        sjt_parent20 = &_parent->datay;
#line 202 "perf2.sj"
                        sjt_functionParam53 = n;
#line 205
                        sjt_functionParam55 = t;
#line 205
                        sjf_f32_tan(sjt_functionParam55, &sjt_capture8);
#line 205
                        sjt_functionParam54 = 1.0f / sjt_capture8;
#line 205
                        sjf_array_f32_setat(sjt_parent20, sjt_functionParam53, sjt_functionParam54);
#line 202
                        n++;
                    }
                } else {
                    if (underscore1 == 4) {
                        int32_t n;
                        int32_t sjt_forEnd5;
                        int32_t sjt_forStart5;

#line 209 "perf2.sj"
                        sjt_forStart5 = 0;
#line 209
                        sjt_forEnd5 = g_dots;
#line 209
                        n = sjt_forStart5;
                        while (n < sjt_forEnd5) {
                            float sjt_capture10;
                            float sjt_capture9;
                            int32_t sjt_functionParam56;
                            int32_t sjt_functionParam57;
                            int32_t sjt_functionParam58;
                            float sjt_functionParam59;
                            int32_t sjt_functionParam60;
                            float sjt_functionParam61;
                            float sjt_functionParam62;
                            float sjt_functionParam63;
                            sjs_array_f32* sjt_parent21 = 0;
                            sjs_array_f32* sjt_parent22 = 0;
                            float t;

#line 210 "perf2.sj"
                            sjt_functionParam56 = 2;
#line 209
                            sjt_functionParam57 = n;
#line 209
                            sjf_test_gettm(_parent, sjt_functionParam56, sjt_functionParam57, &t);
#line 49 "lib/common/array.sj"
                            sjt_parent21 = &_parent->datax;
#line 209 "perf2.sj"
                            sjt_functionParam58 = n;
#line 211
                            sjt_functionParam59 = t;
#line 211
                            sjf_array_f32_setat(sjt_parent21, sjt_functionParam58, sjt_functionParam59);
#line 49 "lib/common/array.sj"
                            sjt_parent22 = &_parent->datay;
#line 209 "perf2.sj"
                            sjt_functionParam60 = n;
#line 212
                            sjt_functionParam62 = t;
#line 212
                            sjf_f32_abs(sjt_functionParam62, &sjt_capture9);
#line 212
                            sjt_functionParam63 = t;
#line 212
                            sjf_f32_sin(sjt_functionParam63, &sjt_capture10);
#line 212
                            sjt_functionParam61 = sjt_capture9 * sjt_capture10;
#line 212
                            sjf_array_f32_setat(sjt_parent22, sjt_functionParam60, sjt_functionParam61);
#line 209
                            n++;
                        }
                    } else {
                        if (underscore1 == 5) {
                            int32_t n;
                            int32_t sjt_forEnd6;
                            int32_t sjt_forStart6;

#line 216 "perf2.sj"
                            sjt_forStart6 = 0;
#line 216
                            sjt_forEnd6 = g_dots;
#line 216
                            n = sjt_forStart6;
                            while (n < sjt_forEnd6) {
                                int32_t sjt_functionParam64;
                                int32_t sjt_functionParam65;
                                int32_t sjt_functionParam66;
                                float sjt_functionParam67;
                                int32_t sjt_functionParam68;
                                float sjt_functionParam69;
                                sjs_array_f32* sjt_parent23 = 0;
                                sjs_array_f32* sjt_parent24 = 0;
                                float t;

#line 217 "perf2.sj"
                                sjt_functionParam64 = 2;
#line 216
                                sjt_functionParam65 = n;
#line 216
                                sjf_test_gettm(_parent, sjt_functionParam64, sjt_functionParam65, &t);
#line 49 "lib/common/array.sj"
                                sjt_parent23 = &_parent->datax;
#line 216 "perf2.sj"
                                sjt_functionParam66 = n;
#line 218
                                sjt_functionParam67 = t;
#line 218
                                sjf_array_f32_setat(sjt_parent23, sjt_functionParam66, sjt_functionParam67);
#line 49 "lib/common/array.sj"
                                sjt_parent24 = &_parent->datay;
#line 216 "perf2.sj"
                                sjt_functionParam68 = n;
#line 219
                                sjt_functionParam69 = t / (t * t);
#line 219
                                sjf_array_f32_setat(sjt_parent24, sjt_functionParam68, sjt_functionParam69);
#line 216
                                n++;
                            }
                        } else {
                            if (underscore1 == 6) {
                                int32_t n;
                                int32_t sjt_forEnd7;
                                int32_t sjt_forStart7;

#line 223 "perf2.sj"
                                sjt_forStart7 = 0;
#line 223
                                sjt_forEnd7 = g_dots;
#line 223
                                n = sjt_forStart7;
                                while (n < sjt_forEnd7) {
                                    float sjt_capture11;
                                    int32_t sjt_functionParam70;
                                    int32_t sjt_functionParam71;
                                    int32_t sjt_functionParam72;
                                    float sjt_functionParam73;
                                    int32_t sjt_functionParam74;
                                    float sjt_functionParam75;
                                    float sjt_functionParam76;
                                    sjs_array_f32* sjt_parent25 = 0;
                                    sjs_array_f32* sjt_parent26 = 0;
                                    float t;

#line 224 "perf2.sj"
                                    sjt_functionParam70 = 2;
#line 223
                                    sjt_functionParam71 = n;
#line 223
                                    sjf_test_gettm(_parent, sjt_functionParam70, sjt_functionParam71, &t);
#line 49 "lib/common/array.sj"
                                    sjt_parent25 = &_parent->datax;
#line 223 "perf2.sj"
                                    sjt_functionParam72 = n;
#line 225
                                    sjt_functionParam73 = t;
#line 225
                                    sjf_array_f32_setat(sjt_parent25, sjt_functionParam72, sjt_functionParam73);
#line 49 "lib/common/array.sj"
                                    sjt_parent26 = &_parent->datay;
#line 223 "perf2.sj"
                                    sjt_functionParam74 = n;
#line 226
                                    sjt_functionParam76 = t;
#line 226
                                    sjf_f32_sin(sjt_functionParam76, &sjt_capture11);
#line 226
                                    sjt_functionParam75 = t * sjt_capture11;
#line 226
                                    sjf_array_f32_setat(sjt_parent26, sjt_functionParam74, sjt_functionParam75);
#line 223
                                    n++;
                                }
                            } else {
                                if (underscore1 == 7) {
                                    int32_t n;
                                    int32_t sjt_forEnd8;
                                    int32_t sjt_forStart8;

#line 230 "perf2.sj"
                                    sjt_forStart8 = 0;
#line 230
                                    sjt_forEnd8 = g_dots;
#line 230
                                    n = sjt_forStart8;
                                    while (n < sjt_forEnd8) {
                                        float sjt_capture12;
                                        float sjt_capture13;
                                        float sjt_capture14;
                                        float sjt_capture15;
                                        int32_t sjt_functionParam77;
                                        int32_t sjt_functionParam78;
                                        int32_t sjt_functionParam79;
                                        float sjt_functionParam80;
                                        float sjt_functionParam81;
                                        float sjt_functionParam82;
                                        int32_t sjt_functionParam83;
                                        float sjt_functionParam84;
                                        float sjt_functionParam85;
                                        float sjt_functionParam86;
                                        sjs_array_f32* sjt_parent27 = 0;
                                        sjs_array_f32* sjt_parent28 = 0;
                                        float t;

#line 231 "perf2.sj"
                                        sjt_functionParam77 = 2;
#line 230
                                        sjt_functionParam78 = n;
#line 230
                                        sjf_test_gett(_parent, sjt_functionParam77, sjt_functionParam78, &t);
#line 49 "lib/common/array.sj"
                                        sjt_parent27 = &_parent->datax;
#line 230 "perf2.sj"
                                        sjt_functionParam79 = n;
#line 232
                                        sjt_functionParam81 = t;
#line 232
                                        sjf_f32_cos(sjt_functionParam81, &sjt_capture12);
#line 232
                                        sjt_functionParam82 = 2.0f * t;
#line 232
                                        sjf_f32_cos(sjt_functionParam82, &sjt_capture13);
#line 232
                                        sjt_functionParam80 = (2.0f * sjt_capture12) + sjt_capture13;
#line 232
                                        sjf_array_f32_setat(sjt_parent27, sjt_functionParam79, sjt_functionParam80);
#line 49 "lib/common/array.sj"
                                        sjt_parent28 = &_parent->datay;
#line 230 "perf2.sj"
                                        sjt_functionParam83 = n;
#line 233
                                        sjt_functionParam85 = t;
#line 233
                                        sjf_f32_sin(sjt_functionParam85, &sjt_capture14);
#line 233
                                        sjt_functionParam86 = 2.0f * t;
#line 233
                                        sjf_f32_sin(sjt_functionParam86, &sjt_capture15);
#line 233
                                        sjt_functionParam84 = (2.0f * sjt_capture14) - sjt_capture15;
#line 233
                                        sjf_array_f32_setat(sjt_parent28, sjt_functionParam83, sjt_functionParam84);
#line 230
                                        n++;
                                    }
                                } else {
                                    if (underscore1 == 8) {
                                        int32_t n;
                                        int32_t sjt_forEnd9;
                                        int32_t sjt_forStart9;

#line 237 "perf2.sj"
                                        sjt_forStart9 = 0;
#line 237
                                        sjt_forEnd9 = g_dots;
#line 237
                                        n = sjt_forStart9;
                                        while (n < sjt_forEnd9) {
                                            float sjt_capture16;
                                            float sjt_capture17;
                                            float sjt_capture18;
                                            float sjt_capture19;
                                            int32_t sjt_functionParam87;
                                            int32_t sjt_functionParam88;
                                            int32_t sjt_functionParam89;
                                            float sjt_functionParam90;
                                            float sjt_functionParam91;
                                            float sjt_functionParam92;
                                            int32_t sjt_functionParam93;
                                            float sjt_functionParam94;
                                            float sjt_functionParam95;
                                            float sjt_functionParam96;
                                            sjs_array_f32* sjt_parent29 = 0;
                                            sjs_array_f32* sjt_parent30 = 0;
                                            float t;

#line 238 "perf2.sj"
                                            sjt_functionParam87 = 2;
#line 237
                                            sjt_functionParam88 = n;
#line 237
                                            sjf_test_gett(_parent, sjt_functionParam87, sjt_functionParam88, &t);
#line 49 "lib/common/array.sj"
                                            sjt_parent29 = &_parent->datax;
#line 237 "perf2.sj"
                                            sjt_functionParam89 = n;
#line 239
                                            sjt_functionParam91 = t;
#line 239
                                            sjf_f32_cos(sjt_functionParam91, &sjt_capture16);
#line 239
                                            sjt_functionParam92 = 5.0f * t;
#line 239
                                            sjf_f32_cos(sjt_functionParam92, &sjt_capture17);
#line 239
                                            sjt_functionParam90 = 4.0f * (sjt_capture16 + (sjt_capture17 / 5.0f));
#line 239
                                            sjf_array_f32_setat(sjt_parent29, sjt_functionParam89, sjt_functionParam90);
#line 49 "lib/common/array.sj"
                                            sjt_parent30 = &_parent->datay;
#line 237 "perf2.sj"
                                            sjt_functionParam93 = n;
#line 241
                                            sjt_functionParam95 = t;
#line 241
                                            sjf_f32_sin(sjt_functionParam95, &sjt_capture18);
#line 241
                                            sjt_functionParam96 = 5.0f * t;
#line 241
                                            sjf_f32_sin(sjt_functionParam96, &sjt_capture19);
#line 241
                                            sjt_functionParam94 = 4.0f * (sjt_capture18 - (sjt_capture19 / 5.0f));
#line 241
                                            sjf_array_f32_setat(sjt_parent30, sjt_functionParam93, sjt_functionParam94);
#line 237
                                            n++;
                                        }
                                    } else {
                                        if (underscore1 == 9) {
                                            int32_t n;
                                            int32_t sjt_forEnd10;
                                            int32_t sjt_forStart10;

#line 246 "perf2.sj"
                                            sjt_forStart10 = 0;
#line 246
                                            sjt_forEnd10 = g_dots;
#line 246
                                            n = sjt_forStart10;
                                            while (n < sjt_forEnd10) {
                                                float sjt_capture20;
                                                float sjt_capture21;
                                                float sjt_capture22;
                                                float sjt_capture23;
                                                float sjt_functionParam100;
                                                float sjt_functionParam101;
                                                float sjt_functionParam102;
                                                int32_t sjt_functionParam103;
                                                float sjt_functionParam104;
                                                float sjt_functionParam105;
                                                float sjt_functionParam106;
                                                int32_t sjt_functionParam97;
                                                int32_t sjt_functionParam98;
                                                int32_t sjt_functionParam99;
                                                sjs_array_f32* sjt_parent31 = 0;
                                                sjs_array_f32* sjt_parent32 = 0;
                                                float t;

#line 247 "perf2.sj"
                                                sjt_functionParam97 = 20;
#line 246
                                                sjt_functionParam98 = n;
#line 246
                                                sjf_test_gett(_parent, sjt_functionParam97, sjt_functionParam98, &t);
#line 49 "lib/common/array.sj"
                                                sjt_parent31 = &_parent->datax;
#line 246 "perf2.sj"
                                                sjt_functionParam99 = n;
#line 248
                                                sjt_functionParam101 = t;
#line 248
                                                sjf_f32_cos(sjt_functionParam101, &sjt_capture20);
#line 248
                                                sjt_functionParam102 = 1.1f * t;
#line 248
                                                sjf_f32_cos(sjt_functionParam102, &sjt_capture21);
#line 248
                                                sjt_functionParam100 = 2.8f * (sjt_capture20 + (sjt_capture21 / 1.1f));
#line 248
                                                sjf_array_f32_setat(sjt_parent31, sjt_functionParam99, sjt_functionParam100);
#line 49 "lib/common/array.sj"
                                                sjt_parent32 = &_parent->datay;
#line 246 "perf2.sj"
                                                sjt_functionParam103 = n;
#line 249
                                                sjt_functionParam105 = t;
#line 249
                                                sjf_f32_sin(sjt_functionParam105, &sjt_capture22);
#line 249
                                                sjt_functionParam106 = 1.1f * t;
#line 249
                                                sjf_f32_sin(sjt_functionParam106, &sjt_capture23);
#line 249
                                                sjt_functionParam104 = 2.8f * (sjt_capture22 - (sjt_capture23 / 1.1f));
#line 249
                                                sjf_array_f32_setat(sjt_parent32, sjt_functionParam103, sjt_functionParam104);
#line 246
                                                n++;
                                            }
                                        } else {
                                            if (underscore1 == 10) {
                                                int32_t n;
                                                int32_t sjt_forEnd11;
                                                int32_t sjt_forStart11;

#line 253 "perf2.sj"
                                                sjt_forStart11 = 0;
#line 253
                                                sjt_forEnd11 = g_dots;
#line 253
                                                n = sjt_forStart11;
                                                while (n < sjt_forEnd11) {
                                                    float sjt_capture24;
                                                    float sjt_capture25;
                                                    float sjt_capture26;
                                                    float sjt_capture27;
                                                    int32_t sjt_functionParam107;
                                                    int32_t sjt_functionParam108;
                                                    int32_t sjt_functionParam109;
                                                    float sjt_functionParam110;
                                                    float sjt_functionParam111;
                                                    float sjt_functionParam112;
                                                    int32_t sjt_functionParam113;
                                                    float sjt_functionParam114;
                                                    float sjt_functionParam115;
                                                    float sjt_functionParam116;
                                                    sjs_array_f32* sjt_parent33 = 0;
                                                    sjs_array_f32* sjt_parent34 = 0;
                                                    float t;

#line 254 "perf2.sj"
                                                    sjt_functionParam107 = 2;
#line 253
                                                    sjt_functionParam108 = n;
#line 253
                                                    sjf_test_gett(_parent, sjt_functionParam107, sjt_functionParam108, &t);
#line 49 "lib/common/array.sj"
                                                    sjt_parent33 = &_parent->datax;
#line 253 "perf2.sj"
                                                    sjt_functionParam109 = n;
#line 255
                                                    sjt_functionParam111 = t;
#line 255
                                                    sjf_f32_cos(sjt_functionParam111, &sjt_capture24);
#line 255
                                                    sjt_functionParam112 = t;
#line 255
                                                    sjf_f32_cos(sjt_functionParam112, &sjt_capture25);
#line 255
                                                    sjt_functionParam110 = (3.0f * (1.0f + sjt_capture24)) * sjt_capture25;
#line 255
                                                    sjf_array_f32_setat(sjt_parent33, sjt_functionParam109, sjt_functionParam110);
#line 49 "lib/common/array.sj"
                                                    sjt_parent34 = &_parent->datay;
#line 253 "perf2.sj"
                                                    sjt_functionParam113 = n;
#line 256
                                                    sjt_functionParam115 = t;
#line 256
                                                    sjf_f32_cos(sjt_functionParam115, &sjt_capture26);
#line 256
                                                    sjt_functionParam116 = t;
#line 256
                                                    sjf_f32_sin(sjt_functionParam116, &sjt_capture27);
#line 256
                                                    sjt_functionParam114 = (3.0f * (1.0f + sjt_capture26)) * sjt_capture27;
#line 256
                                                    sjf_array_f32_setat(sjt_parent34, sjt_functionParam113, sjt_functionParam114);
#line 253
                                                    n++;
                                                }
                                            } else {
                                                if (underscore1 == 11) {
                                                    int32_t n;
                                                    int32_t sjt_forEnd12;
                                                    int32_t sjt_forStart12;

#line 260 "perf2.sj"
                                                    sjt_forStart12 = 0;
#line 260
                                                    sjt_forEnd12 = g_dots;
#line 260
                                                    n = sjt_forStart12;
                                                    while (n < sjt_forEnd12) {
                                                        float sjt_capture28;
                                                        float sjt_capture29;
                                                        int32_t sjt_functionParam117;
                                                        int32_t sjt_functionParam118;
                                                        int32_t sjt_functionParam119;
                                                        float sjt_functionParam120;
                                                        float sjt_functionParam121;
                                                        int32_t sjt_functionParam122;
                                                        float sjt_functionParam123;
                                                        float sjt_functionParam124;
                                                        sjs_array_f32* sjt_parent35 = 0;
                                                        sjs_array_f32* sjt_parent36 = 0;
                                                        float t;

#line 261 "perf2.sj"
                                                        sjt_functionParam117 = 2;
#line 260
                                                        sjt_functionParam118 = n;
#line 260
                                                        sjf_test_gett(_parent, sjt_functionParam117, sjt_functionParam118, &t);
#line 49 "lib/common/array.sj"
                                                        sjt_parent35 = &_parent->datax;
#line 260 "perf2.sj"
                                                        sjt_functionParam119 = n;
#line 262
                                                        sjt_functionParam121 = t + (g_f32_pi / 2.0f);
#line 262
                                                        sjf_f32_sin(sjt_functionParam121, &sjt_capture28);
#line 262
                                                        sjt_functionParam120 = 3.0f * sjt_capture28;
#line 262
                                                        sjf_array_f32_setat(sjt_parent35, sjt_functionParam119, sjt_functionParam120);
#line 49 "lib/common/array.sj"
                                                        sjt_parent36 = &_parent->datay;
#line 260 "perf2.sj"
                                                        sjt_functionParam122 = n;
#line 263
                                                        sjt_functionParam124 = 2.0f * t;
#line 263
                                                        sjf_f32_sin(sjt_functionParam124, &sjt_capture29);
#line 263
                                                        sjt_functionParam123 = 3.0f * sjt_capture29;
#line 263
                                                        sjf_array_f32_setat(sjt_parent36, sjt_functionParam122, sjt_functionParam123);
#line 260
                                                        n++;
                                                    }
                                                } else {
                                                    if (underscore1 == 12) {
                                                        int32_t n;
                                                        int32_t sjt_forEnd13;
                                                        int32_t sjt_forStart13;

#line 268 "perf2.sj"
                                                        sjt_forStart13 = 0;
#line 268
                                                        sjt_forEnd13 = g_dots;
#line 268
                                                        n = sjt_forStart13;
                                                        while (n < sjt_forEnd13) {
                                                            float sjt_capture30;
                                                            float sjt_capture31;
                                                            float sjt_capture32;
                                                            float sjt_capture33;
                                                            float sjt_capture34;
                                                            float sjt_capture35;
                                                            float sjt_capture36;
                                                            float sjt_capture37;
                                                            int32_t sjt_functionParam125;
                                                            int32_t sjt_functionParam126;
                                                            int32_t sjt_functionParam127;
                                                            float sjt_functionParam128;
                                                            float sjt_functionParam129;
                                                            float sjt_functionParam130;
                                                            float sjt_functionParam131;
                                                            float sjt_functionParam132;
                                                            float sjt_functionParam133;
                                                            float sjt_functionParam134;
                                                            float sjt_functionParam135;
                                                            int32_t sjt_functionParam136;
                                                            float sjt_functionParam137;
                                                            float sjt_functionParam138;
                                                            float sjt_functionParam139;
                                                            float sjt_functionParam140;
                                                            float sjt_functionParam141;
                                                            float sjt_functionParam142;
                                                            float sjt_functionParam143;
                                                            float sjt_functionParam144;
                                                            sjs_array_f32* sjt_parent37 = 0;
                                                            sjs_array_f32* sjt_parent38 = 0;
                                                            float t;

#line 269 "perf2.sj"
                                                            sjt_functionParam125 = 12;
#line 268
                                                            sjt_functionParam126 = n;
#line 268
                                                            sjf_test_gett(_parent, sjt_functionParam125, sjt_functionParam126, &t);
#line 49 "lib/common/array.sj"
                                                            sjt_parent37 = &_parent->datax;
#line 268 "perf2.sj"
                                                            sjt_functionParam127 = n;
#line 270
                                                            sjt_functionParam129 = t;
#line 270
                                                            sjf_f32_sin(sjt_functionParam129, &sjt_capture30);
#line 270
                                                            sjt_functionParam131 = t;
#line 270
                                                            sjf_f32_cos(sjt_functionParam131, &sjt_functionParam130);
#line 270
                                                            sjf_f32_exp(sjt_functionParam130, &sjt_capture31);
#line 270
                                                            sjt_functionParam132 = 4.0f * t;
#line 270
                                                            sjf_f32_cos(sjt_functionParam132, &sjt_capture32);
#line 270
                                                            sjt_functionParam134 = t / 12.0f;
#line 270
                                                            sjf_f32_sin(sjt_functionParam134, &sjt_functionParam133);
#line 270
                                                            sjt_functionParam135 = 5.0f;
#line 270
                                                            sjf_f32_pow(sjt_functionParam133, sjt_functionParam135, &sjt_capture33);
#line 270
                                                            sjt_functionParam128 = sjt_capture30 * ((sjt_capture31 - (2.0f * sjt_capture32)) + sjt_capture33);
#line 270
                                                            sjf_array_f32_setat(sjt_parent37, sjt_functionParam127, sjt_functionParam128);
#line 49 "lib/common/array.sj"
                                                            sjt_parent38 = &_parent->datay;
#line 268 "perf2.sj"
                                                            sjt_functionParam136 = n;
#line 271
                                                            sjt_functionParam138 = t;
#line 271
                                                            sjf_f32_cos(sjt_functionParam138, &sjt_capture34);
#line 271
                                                            sjt_functionParam140 = t;
#line 271
                                                            sjf_f32_cos(sjt_functionParam140, &sjt_functionParam139);
#line 271
                                                            sjf_f32_exp(sjt_functionParam139, &sjt_capture35);
#line 271
                                                            sjt_functionParam141 = 4.0f * t;
#line 271
                                                            sjf_f32_cos(sjt_functionParam141, &sjt_capture36);
#line 271
                                                            sjt_functionParam143 = t / 12.0f;
#line 271
                                                            sjf_f32_sin(sjt_functionParam143, &sjt_functionParam142);
#line 271
                                                            sjt_functionParam144 = 5.0f;
#line 271
                                                            sjf_f32_pow(sjt_functionParam142, sjt_functionParam144, &sjt_capture37);
#line 271
                                                            sjt_functionParam137 = sjt_capture34 * ((sjt_capture35 - (2.0f * sjt_capture36)) + sjt_capture37);
#line 271
                                                            sjf_array_f32_setat(sjt_parent38, sjt_functionParam136, sjt_functionParam137);
#line 268
                                                            n++;
                                                        }
                                                    } else {
                                                        if (underscore1 == 13) {
                                                            int32_t n;
                                                            int32_t sjt_forEnd14;
                                                            int32_t sjt_forStart14;

#line 276 "perf2.sj"
                                                            sjt_forStart14 = 0;
#line 276
                                                            sjt_forEnd14 = g_dots;
#line 276
                                                            n = sjt_forStart14;
                                                            while (n < sjt_forEnd14) {
                                                                float sjt_capture38;
                                                                float sjt_capture39;
                                                                float sjt_capture40;
                                                                float sjt_capture41;
                                                                float sjt_capture42;
                                                                int32_t sjt_functionParam145;
                                                                int32_t sjt_functionParam146;
                                                                int32_t sjt_functionParam147;
                                                                float sjt_functionParam148;
                                                                float sjt_functionParam149;
                                                                float sjt_functionParam150;
                                                                float sjt_functionParam151;
                                                                int32_t sjt_functionParam152;
                                                                float sjt_functionParam153;
                                                                float sjt_functionParam154;
                                                                float sjt_functionParam155;
                                                                float sjt_functionParam156;
                                                                float sjt_functionParam157;
                                                                sjs_array_f32* sjt_parent39 = 0;
                                                                sjs_array_f32* sjt_parent40 = 0;
                                                                float t;

#line 277 "perf2.sj"
                                                                sjt_functionParam145 = 2;
#line 276
                                                                sjt_functionParam146 = n;
#line 276
                                                                sjf_test_gett(_parent, sjt_functionParam145, sjt_functionParam146, &t);
#line 49 "lib/common/array.sj"
                                                                sjt_parent39 = &_parent->datax;
#line 276 "perf2.sj"
                                                                sjt_functionParam147 = n;
#line 278
                                                                sjt_functionParam150 = t;
#line 278
                                                                sjf_f32_sin(sjt_functionParam150, &sjt_functionParam149);
#line 278
                                                                sjt_functionParam151 = 3.0f;
#line 278
                                                                sjf_f32_pow(sjt_functionParam149, sjt_functionParam151, &sjt_capture38);
#line 278
                                                                sjt_functionParam148 = (16.0f * sjt_capture38) / 4.0f;
#line 278
                                                                sjf_array_f32_setat(sjt_parent39, sjt_functionParam147, sjt_functionParam148);
#line 49 "lib/common/array.sj"
                                                                sjt_parent40 = &_parent->datay;
#line 276 "perf2.sj"
                                                                sjt_functionParam152 = n;
#line 279
                                                                sjt_functionParam154 = t;
#line 279
                                                                sjf_f32_cos(sjt_functionParam154, &sjt_capture39);
#line 279
                                                                sjt_functionParam155 = 2.0f * t;
#line 279
                                                                sjf_f32_cos(sjt_functionParam155, &sjt_capture40);
#line 279
                                                                sjt_functionParam156 = 3.0f * t;
#line 279
                                                                sjf_f32_cos(sjt_functionParam156, &sjt_capture41);
#line 279
                                                                sjt_functionParam157 = 4.0f * t;
#line 279
                                                                sjf_f32_cos(sjt_functionParam157, &sjt_capture42);
#line 279
                                                                sjt_functionParam153 = ((((13.0f * sjt_capture39) - (5.0f * sjt_capture40)) - (2.0f * sjt_capture41)) - sjt_capture42) / 4.0f;
#line 279
                                                                sjf_array_f32_setat(sjt_parent40, sjt_functionParam152, sjt_functionParam153);
#line 276
                                                                n++;
                                                            }
                                                        } else {
                                                            if (underscore1 == 14) {
                                                                int32_t n;
                                                                int32_t sjt_forEnd15;
                                                                int32_t sjt_forStart15;

#line 283 "perf2.sj"
                                                                sjt_forStart15 = 0;
#line 283
                                                                sjt_forEnd15 = g_dots;
#line 283
                                                                n = sjt_forStart15;
                                                                while (n < sjt_forEnd15) {
                                                                    float sjt_capture43;
                                                                    float sjt_capture44;
                                                                    int32_t sjt_functionParam158;
                                                                    int32_t sjt_functionParam159;
                                                                    int32_t sjt_functionParam160;
                                                                    float sjt_functionParam161;
                                                                    float sjt_functionParam162;
                                                                    int32_t sjt_functionParam163;
                                                                    float sjt_functionParam164;
                                                                    float sjt_functionParam165;
                                                                    sjs_array_f32* sjt_parent41 = 0;
                                                                    sjs_array_f32* sjt_parent42 = 0;
                                                                    float t;

#line 284 "perf2.sj"
                                                                    sjt_functionParam158 = 1;
#line 283
                                                                    sjt_functionParam159 = n;
#line 283
                                                                    sjf_test_gettm(_parent, sjt_functionParam158, sjt_functionParam159, &t);
#line 49 "lib/common/array.sj"
                                                                    sjt_parent41 = &_parent->datax;
#line 283 "perf2.sj"
                                                                    sjt_functionParam160 = n;
#line 285
                                                                    sjt_functionParam162 = t;
#line 285
                                                                    sjf_f32_sin(sjt_functionParam162, &sjt_capture43);
#line 285
                                                                    sjt_functionParam161 = 5.0f * sjt_capture43;
#line 285
                                                                    sjf_array_f32_setat(sjt_parent41, sjt_functionParam160, sjt_functionParam161);
#line 49 "lib/common/array.sj"
                                                                    sjt_parent42 = &_parent->datay;
#line 283 "perf2.sj"
                                                                    sjt_functionParam163 = n;
#line 286
                                                                    sjt_functionParam165 = t;
#line 286
                                                                    sjf_f32_cos(sjt_functionParam165, &sjt_capture44);
#line 286
                                                                    sjt_functionParam164 = 5.0f * sjt_capture44;
#line 286
                                                                    sjf_array_f32_setat(sjt_parent42, sjt_functionParam163, sjt_functionParam164);
#line 283
                                                                    n++;
                                                                }
                                                            } else {
                                                                if (underscore1 == 15) {
                                                                    int32_t n;
                                                                    int32_t sjt_forEnd16;
                                                                    int32_t sjt_forStart16;

#line 290 "perf2.sj"
                                                                    sjt_forStart16 = 0;
#line 290
                                                                    sjt_forEnd16 = g_dots;
#line 290
                                                                    n = sjt_forStart16;
                                                                    while (n < sjt_forEnd16) {
                                                                        float sjt_capture45;
                                                                        float sjt_capture46;
                                                                        float sjt_capture47;
                                                                        float sjt_capture48;
                                                                        int32_t sjt_functionParam166;
                                                                        int32_t sjt_functionParam167;
                                                                        int32_t sjt_functionParam168;
                                                                        float sjt_functionParam169;
                                                                        float sjt_functionParam170;
                                                                        float sjt_functionParam171;
                                                                        float sjt_functionParam172;
                                                                        float sjt_functionParam173;
                                                                        int32_t sjt_functionParam174;
                                                                        float sjt_functionParam175;
                                                                        float sjt_functionParam176;
                                                                        float sjt_functionParam177;
                                                                        float sjt_functionParam178;
                                                                        float sjt_functionParam179;
                                                                        sjs_array_f32* sjt_parent43 = 0;
                                                                        sjs_array_f32* sjt_parent44 = 0;
                                                                        float t;

#line 291 "perf2.sj"
                                                                        sjt_functionParam166 = 1;
#line 290
                                                                        sjt_functionParam167 = n;
#line 290
                                                                        sjf_test_gettm(_parent, sjt_functionParam166, sjt_functionParam167, &t);
#line 49 "lib/common/array.sj"
                                                                        sjt_parent43 = &_parent->datax;
#line 290 "perf2.sj"
                                                                        sjt_functionParam168 = n;
#line 292
                                                                        sjt_functionParam170 = t;
#line 292
                                                                        sjf_f32_cos(sjt_functionParam170, &sjt_capture45);
#line 292
                                                                        sjt_functionParam172 = 80.0f * t;
#line 292
                                                                        sjf_f32_cos(sjt_functionParam172, &sjt_functionParam171);
#line 292
                                                                        sjt_functionParam173 = 3.0f;
#line 292
                                                                        sjf_f32_pow(sjt_functionParam171, sjt_functionParam173, &sjt_capture46);
#line 292
                                                                        sjt_functionParam169 = (sjt_capture45 + sjt_capture46) * 3.0f;
#line 292
                                                                        sjf_array_f32_setat(sjt_parent43, sjt_functionParam168, sjt_functionParam169);
#line 49 "lib/common/array.sj"
                                                                        sjt_parent44 = &_parent->datay;
#line 290 "perf2.sj"
                                                                        sjt_functionParam174 = n;
#line 293
                                                                        sjt_functionParam176 = 80.0f * t;
#line 293
                                                                        sjf_f32_sin(sjt_functionParam176, &sjt_capture47);
#line 293
                                                                        sjt_functionParam178 = t;
#line 293
                                                                        sjf_f32_sin(sjt_functionParam178, &sjt_functionParam177);
#line 293
                                                                        sjt_functionParam179 = 4.0f;
#line 293
                                                                        sjf_f32_pow(sjt_functionParam177, sjt_functionParam179, &sjt_capture48);
#line 293
                                                                        sjt_functionParam175 = (sjt_capture47 + sjt_capture48) * 2.5f;
#line 293
                                                                        sjf_array_f32_setat(sjt_parent44, sjt_functionParam174, sjt_functionParam175);
#line 290
                                                                        n++;
                                                                    }
                                                                } else {
                                                                    if (underscore1 == 16) {
                                                                        int32_t n;
                                                                        int32_t sjt_forEnd17;
                                                                        int32_t sjt_forStart17;

#line 297 "perf2.sj"
                                                                        sjt_forStart17 = 0;
#line 297
                                                                        sjt_forEnd17 = g_dots;
#line 297
                                                                        n = sjt_forStart17;
                                                                        while (n < sjt_forEnd17) {
                                                                            float sjt_capture49;
                                                                            float sjt_capture50;
                                                                            float sjt_capture51;
                                                                            float sjt_capture52;
                                                                            float sjt_capture53;
                                                                            float sjt_capture54;
                                                                            float sjt_capture55;
                                                                            float sjt_capture56;
                                                                            float sjt_capture57;
                                                                            float sjt_capture58;
                                                                            float sjt_capture59;
                                                                            float sjt_capture60;
                                                                            int32_t sjt_functionParam180;
                                                                            int32_t sjt_functionParam181;
                                                                            int32_t sjt_functionParam182;
                                                                            float sjt_functionParam183;
                                                                            float sjt_functionParam184;
                                                                            float sjt_functionParam185;
                                                                            float sjt_functionParam186;
                                                                            float sjt_functionParam187;
                                                                            float sjt_functionParam188;
                                                                            float sjt_functionParam189;
                                                                            float sjt_functionParam190;
                                                                            float sjt_functionParam191;
                                                                            float sjt_functionParam192;
                                                                            float sjt_functionParam193;
                                                                            float sjt_functionParam194;
                                                                            float sjt_functionParam195;
                                                                            float sjt_functionParam196;
                                                                            float sjt_functionParam197;
                                                                            int32_t sjt_functionParam198;
                                                                            float sjt_functionParam199;
                                                                            float sjt_functionParam200;
                                                                            float sjt_functionParam201;
                                                                            float sjt_functionParam202;
                                                                            float sjt_functionParam203;
                                                                            float sjt_functionParam204;
                                                                            float sjt_functionParam205;
                                                                            float sjt_functionParam206;
                                                                            float sjt_functionParam207;
                                                                            float sjt_functionParam208;
                                                                            float sjt_functionParam209;
                                                                            float sjt_functionParam210;
                                                                            float sjt_functionParam211;
                                                                            float sjt_functionParam212;
                                                                            float sjt_functionParam213;
                                                                            sjs_array_f32* sjt_parent45 = 0;
                                                                            sjs_array_f32* sjt_parent46 = 0;
                                                                            float t;

#line 298 "perf2.sj"
                                                                            sjt_functionParam180 = 1;
#line 297
                                                                            sjt_functionParam181 = n;
#line 297
                                                                            sjf_test_gettm(_parent, sjt_functionParam180, sjt_functionParam181, &t);
#line 49 "lib/common/array.sj"
                                                                            sjt_parent45 = &_parent->datax;
#line 297 "perf2.sj"
                                                                            sjt_functionParam182 = n;
#line 299
                                                                            sjt_functionParam184 = t;
#line 299
                                                                            sjf_f32_cos(sjt_functionParam184, &sjt_capture49);
#line 299
                                                                            sjt_functionParam187 = t;
#line 299
                                                                            sjf_f32_sin(sjt_functionParam187, &sjt_functionParam186);
#line 299
                                                                            sjt_functionParam188 = 2.0f;
#line 299
                                                                            sjf_f32_pow(sjt_functionParam186, sjt_functionParam188, &sjt_capture50);
#line 299
                                                                            sjt_functionParam190 = t;
#line 299
                                                                            sjf_f32_cos(sjt_functionParam190, &sjt_functionParam189);
#line 299
                                                                            sjt_functionParam191 = 2.0f;
#line 299
                                                                            sjf_f32_pow(sjt_functionParam189, sjt_functionParam191, &sjt_capture51);
#line 299
                                                                            sjt_functionParam193 = t;
#line 299
                                                                            sjf_f32_sin(sjt_functionParam193, &sjt_functionParam192);
#line 299
                                                                            sjt_functionParam194 = 2.0f;
#line 299
                                                                            sjf_f32_pow(sjt_functionParam192, sjt_functionParam194, &sjt_capture52);
#line 299
                                                                            sjt_functionParam196 = t;
#line 299
                                                                            sjf_f32_cos(sjt_functionParam196, &sjt_functionParam195);
#line 299
                                                                            sjt_functionParam197 = 2.0f;
#line 299
                                                                            sjf_f32_pow(sjt_functionParam195, sjt_functionParam197, &sjt_capture53);
#line 299
                                                                            sjt_functionParam185 = (((2.0f * 2.0f) * sjt_capture50) - ((5.0f * 5.0f) * sjt_capture51)) / (sjt_capture52 - sjt_capture53);
#line 299
                                                                            sjf_f32_sqrt(sjt_functionParam185, &sjt_capture54);
#line 299
                                                                            sjt_functionParam183 = sjt_capture49 * sjt_capture54;
#line 299
                                                                            sjf_array_f32_setat(sjt_parent45, sjt_functionParam182, sjt_functionParam183);
#line 49 "lib/common/array.sj"
                                                                            sjt_parent46 = &_parent->datay;
#line 297 "perf2.sj"
                                                                            sjt_functionParam198 = n;
#line 300
                                                                            sjt_functionParam200 = t;
#line 300
                                                                            sjf_f32_sin(sjt_functionParam200, &sjt_capture55);
#line 300
                                                                            sjt_functionParam203 = t;
#line 300
                                                                            sjf_f32_sin(sjt_functionParam203, &sjt_functionParam202);
#line 300
                                                                            sjt_functionParam204 = 2.0f;
#line 300
                                                                            sjf_f32_pow(sjt_functionParam202, sjt_functionParam204, &sjt_capture56);
#line 300
                                                                            sjt_functionParam206 = t;
#line 300
                                                                            sjf_f32_cos(sjt_functionParam206, &sjt_functionParam205);
#line 300
                                                                            sjt_functionParam207 = 2.0f;
#line 300
                                                                            sjf_f32_pow(sjt_functionParam205, sjt_functionParam207, &sjt_capture57);
#line 300
                                                                            sjt_functionParam209 = t;
#line 300
                                                                            sjf_f32_sin(sjt_functionParam209, &sjt_functionParam208);
#line 300
                                                                            sjt_functionParam210 = 2.0f;
#line 300
                                                                            sjf_f32_pow(sjt_functionParam208, sjt_functionParam210, &sjt_capture58);
#line 300
                                                                            sjt_functionParam212 = t;
#line 300
                                                                            sjf_f32_cos(sjt_functionParam212, &sjt_functionParam211);
#line 300
                                                                            sjt_functionParam213 = 2.0f;
#line 300
                                                                            sjf_f32_pow(sjt_functionParam211, sjt_functionParam213, &sjt_capture59);
#line 300
                                                                            sjt_functionParam201 = (((2.0f * 2.0f) * sjt_capture56) - ((5.0f * 5.0f) * sjt_capture57)) / (sjt_capture58 - sjt_capture59);
#line 300
                                                                            sjf_f32_sqrt(sjt_functionParam201, &sjt_capture60);
#line 300
                                                                            sjt_functionParam199 = sjt_capture55 * sjt_capture60;
#line 300
                                                                            sjf_array_f32_setat(sjt_parent46, sjt_functionParam198, sjt_functionParam199);
#line 297
                                                                            n++;
                                                                        }
                                                                    } else {
                                                                        if (underscore1 == 17) {
                                                                            int32_t n;
                                                                            int32_t sjt_forEnd18;
                                                                            int32_t sjt_forStart18;

#line 304 "perf2.sj"
                                                                            sjt_forStart18 = 0;
#line 304
                                                                            sjt_forEnd18 = g_dots;
#line 304
                                                                            n = sjt_forStart18;
                                                                            while (n < sjt_forEnd18) {
                                                                                float sjt_capture61;
                                                                                float sjt_capture62;
                                                                                float sjt_capture63;
                                                                                float sjt_capture64;
                                                                                int32_t sjt_functionParam214;
                                                                                int32_t sjt_functionParam215;
                                                                                int32_t sjt_functionParam216;
                                                                                float sjt_functionParam217;
                                                                                float sjt_functionParam218;
                                                                                float sjt_functionParam219;
                                                                                float sjt_functionParam220;
                                                                                float sjt_functionParam221;
                                                                                int32_t sjt_functionParam222;
                                                                                float sjt_functionParam223;
                                                                                float sjt_functionParam224;
                                                                                float sjt_functionParam225;
                                                                                float sjt_functionParam226;
                                                                                float sjt_functionParam227;
                                                                                sjs_array_f32* sjt_parent47 = 0;
                                                                                sjs_array_f32* sjt_parent48 = 0;
                                                                                float t;

#line 305 "perf2.sj"
                                                                                sjt_functionParam214 = 1;
#line 304
                                                                                sjt_functionParam215 = n;
#line 304
                                                                                sjf_test_gettm(_parent, sjt_functionParam214, sjt_functionParam215, &t);
#line 49 "lib/common/array.sj"
                                                                                sjt_parent47 = &_parent->datax;
#line 304 "perf2.sj"
                                                                                sjt_functionParam216 = n;
#line 306
                                                                                sjt_functionParam218 = t;
#line 306
                                                                                sjf_f32_cos(sjt_functionParam218, &sjt_capture61);
#line 306
                                                                                sjt_functionParam220 = t;
#line 306
                                                                                sjf_f32_sin(sjt_functionParam220, &sjt_functionParam219);
#line 306
                                                                                sjt_functionParam221 = 2.0f;
#line 306
                                                                                sjf_f32_pow(sjt_functionParam219, sjt_functionParam221, &sjt_capture62);
#line 306
                                                                                sjt_functionParam217 = (3.0f * sjt_capture61) * (1.0f - (2.0f * sjt_capture62));
#line 306
                                                                                sjf_array_f32_setat(sjt_parent47, sjt_functionParam216, sjt_functionParam217);
#line 49 "lib/common/array.sj"
                                                                                sjt_parent48 = &_parent->datay;
#line 304 "perf2.sj"
                                                                                sjt_functionParam222 = n;
#line 307
                                                                                sjt_functionParam224 = t;
#line 307
                                                                                sjf_f32_sin(sjt_functionParam224, &sjt_capture63);
#line 307
                                                                                sjt_functionParam226 = t;
#line 307
                                                                                sjf_f32_cos(sjt_functionParam226, &sjt_functionParam225);
#line 307
                                                                                sjt_functionParam227 = 2.0f;
#line 307
                                                                                sjf_f32_pow(sjt_functionParam225, sjt_functionParam227, &sjt_capture64);
#line 307
                                                                                sjt_functionParam223 = (3.0f * sjt_capture63) * (1.0f - (2.0f * sjt_capture64));
#line 307
                                                                                sjf_array_f32_setat(sjt_parent48, sjt_functionParam222, sjt_functionParam223);
#line 304
                                                                                n++;
                                                                            }
                                                                        } else {
#line 312 "perf2.sj"
                                                                            _parent->funcid = 18;
#line 313
                                                                            g_persp = 50.0f;
#line 313
                                                                            sjf_test_imgdata_functionlist(_parent);
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void sjf_test_copy(sjs_test* _this, sjs_test* _from) {
#line 50 "perf2.sj"
    _this->funcid = _from->funcid;
#line 50
    _this->lastfuncid = _from->lastfuncid;
#line 50
    _this->datax._refCount = 1;
#line 50
    sjf_array_f32_copy(&_this->datax, &_from->datax);
#line 50
    _this->datay._refCount = 1;
#line 50
    sjf_array_f32_copy(&_this->datay, &_from->datay);
#line 50
    _this->rotatex = _from->rotatex;
#line 50
    _this->rotatey = _from->rotatey;
#line 50
    _this->rotatez = _from->rotatez;
#line 50
    _this->datavert1x._refCount = 1;
#line 50
    sjf_array_f32_copy(&_this->datavert1x, &_from->datavert1x);
#line 50
    _this->datavert1y._refCount = 1;
#line 50
    sjf_array_f32_copy(&_this->datavert1y, &_from->datavert1y);
#line 50
    _this->datavert2x._refCount = 1;
#line 50
    sjf_array_f32_copy(&_this->datavert2x, &_from->datavert2x);
#line 50
    _this->datavert2y._refCount = 1;
#line 50
    sjf_array_f32_copy(&_this->datavert2y, &_from->datavert2y);
#line 50
    _this->datavert3x._refCount = 1;
#line 50
    sjf_array_f32_copy(&_this->datavert3x, &_from->datavert3x);
#line 50
    _this->datavert3y._refCount = 1;
#line 50
    sjf_array_f32_copy(&_this->datavert3y, &_from->datavert3y);
#line 50
    _this->datavert4x._refCount = 1;
#line 50
    sjf_array_f32_copy(&_this->datavert4x, &_from->datavert4x);
#line 50
    _this->datavert4y._refCount = 1;
#line 50
    sjf_array_f32_copy(&_this->datavert4y, &_from->datavert4y);
#line 50
    _this->datavert5x._refCount = 1;
#line 50
    sjf_array_f32_copy(&_this->datavert5x, &_from->datavert5x);
#line 50
    _this->datavert5y._refCount = 1;
#line 50
    sjf_array_f32_copy(&_this->datavert5y, &_from->datavert5y);
#line 50
    _this->datahotizont1x._refCount = 1;
#line 50
    sjf_array_f32_copy(&_this->datahotizont1x, &_from->datahotizont1x);
#line 50
    _this->datahotizont1y._refCount = 1;
#line 50
    sjf_array_f32_copy(&_this->datahotizont1y, &_from->datahotizont1y);
#line 50
    _this->datahotizont2x._refCount = 1;
#line 50
    sjf_array_f32_copy(&_this->datahotizont2x, &_from->datahotizont2x);
#line 50
    _this->datahotizont2y._refCount = 1;
#line 50
    sjf_array_f32_copy(&_this->datahotizont2y, &_from->datahotizont2y);
#line 50
    _this->datahotizont3x._refCount = 1;
#line 50
    sjf_array_f32_copy(&_this->datahotizont3x, &_from->datahotizont3x);
#line 50
    _this->datahotizont3y._refCount = 1;
#line 50
    sjf_array_f32_copy(&_this->datahotizont3y, &_from->datahotizont3y);
#line 50
    _this->datahotizont4x._refCount = 1;
#line 50
    sjf_array_f32_copy(&_this->datahotizont4x, &_from->datahotizont4x);
#line 50
    _this->datahotizont4y._refCount = 1;
#line 50
    sjf_array_f32_copy(&_this->datahotizont4y, &_from->datahotizont4y);
#line 50
    _this->datahotizont5x._refCount = 1;
#line 50
    sjf_array_f32_copy(&_this->datahotizont5x, &_from->datahotizont5x);
#line 50
    _this->datahotizont5y._refCount = 1;
#line 50
    sjf_array_f32_copy(&_this->datahotizont5y, &_from->datahotizont5y);
#line 50
    _this->_rect._refCount = 1;
#line 50
    sjf_rect_copy(&_this->_rect, &_from->_rect);
}

void sjf_test_destroy(sjs_test* _this) {
    if (_this->datax._refCount == 1) { sjf_array_f32_destroy(&_this->datax); }
;
    if (_this->datay._refCount == 1) { sjf_array_f32_destroy(&_this->datay); }
;
    if (_this->datavert1x._refCount == 1) { sjf_array_f32_destroy(&_this->datavert1x); }
;
    if (_this->datavert1y._refCount == 1) { sjf_array_f32_destroy(&_this->datavert1y); }
;
    if (_this->datavert2x._refCount == 1) { sjf_array_f32_destroy(&_this->datavert2x); }
;
    if (_this->datavert2y._refCount == 1) { sjf_array_f32_destroy(&_this->datavert2y); }
;
    if (_this->datavert3x._refCount == 1) { sjf_array_f32_destroy(&_this->datavert3x); }
;
    if (_this->datavert3y._refCount == 1) { sjf_array_f32_destroy(&_this->datavert3y); }
;
    if (_this->datavert4x._refCount == 1) { sjf_array_f32_destroy(&_this->datavert4x); }
;
    if (_this->datavert4y._refCount == 1) { sjf_array_f32_destroy(&_this->datavert4y); }
;
    if (_this->datavert5x._refCount == 1) { sjf_array_f32_destroy(&_this->datavert5x); }
;
    if (_this->datavert5y._refCount == 1) { sjf_array_f32_destroy(&_this->datavert5y); }
;
    if (_this->datahotizont1x._refCount == 1) { sjf_array_f32_destroy(&_this->datahotizont1x); }
;
    if (_this->datahotizont1y._refCount == 1) { sjf_array_f32_destroy(&_this->datahotizont1y); }
;
    if (_this->datahotizont2x._refCount == 1) { sjf_array_f32_destroy(&_this->datahotizont2x); }
;
    if (_this->datahotizont2y._refCount == 1) { sjf_array_f32_destroy(&_this->datahotizont2y); }
;
    if (_this->datahotizont3x._refCount == 1) { sjf_array_f32_destroy(&_this->datahotizont3x); }
;
    if (_this->datahotizont3y._refCount == 1) { sjf_array_f32_destroy(&_this->datahotizont3y); }
;
    if (_this->datahotizont4x._refCount == 1) { sjf_array_f32_destroy(&_this->datahotizont4x); }
;
    if (_this->datahotizont4y._refCount == 1) { sjf_array_f32_destroy(&_this->datahotizont4y); }
;
    if (_this->datahotizont5x._refCount == 1) { sjf_array_f32_destroy(&_this->datahotizont5x); }
;
    if (_this->datahotizont5y._refCount == 1) { sjf_array_f32_destroy(&_this->datahotizont5y); }
;
    if (_this->_rect._refCount == 1) { sjf_rect_destroy(&_this->_rect); }
;
}

void sjf_test_findaxis(sjs_test* _parent) {
    bool result17;
    bool sjt_capture65;
    bool sjt_capture92;
    bool sjt_capture93;
    int32_t sjt_functionParam270;
    int32_t sjt_functionParam330;
    sjs_array_bool* sjt_parent111 = 0;
    sjs_array_bool* sjt_parent69 = 0;

#line 7 "lib/common/array.sj"
    sjt_parent69 = &g_mainrot;
#line 320 "perf2.sj"
    sjt_functionParam270 = 0;
#line 320
    sjf_array_bool_getat(sjt_parent69, sjt_functionParam270, &sjt_capture65);
#line 320
    result17 = !sjt_capture65;
    if (result17) {
        bool result19;
        bool sjt_capture66;
        bool sjt_capture67;
        bool sjt_capture78;
        bool sjt_capture79;
        int32_t sjt_functionParam271;
        int32_t sjt_functionParam289;
        sjs_array_bool* sjt_parent70 = 0;
        sjs_array_bool* sjt_parent84 = 0;

#line 7 "lib/common/array.sj"
        sjt_parent70 = &g_stateof;
#line 321 "perf2.sj"
        sjt_functionParam271 = 0;
#line 321
        sjf_array_bool_getat(sjt_parent70, sjt_functionParam271, &sjt_capture67);
        if (sjt_capture67) {
            bool sjt_capture68;
            bool sjt_capture69;
            int32_t sjt_functionParam272;
            sjs_array_bool* sjt_parent71 = 0;

#line 7 "lib/common/array.sj"
            sjt_parent71 = &g_stateof;
#line 321 "perf2.sj"
            sjt_functionParam272 = 1;
#line 321
            sjf_array_bool_getat(sjt_parent71, sjt_functionParam272, &sjt_capture69);
            if (sjt_capture69) {
                bool sjt_capture70;
                int32_t sjt_functionParam273;
                sjs_array_bool* sjt_parent72 = 0;

#line 7 "lib/common/array.sj"
                sjt_parent72 = &g_stateof;
#line 321 "perf2.sj"
                sjt_functionParam273 = 2;
#line 321
                sjf_array_bool_getat(sjt_parent72, sjt_functionParam273, &sjt_capture70);
#line 321
                sjt_capture68 = sjt_capture70;
            } else {
#line 321 "perf2.sj"
                sjt_capture68 = false;
            }

#line 321
            sjt_capture66 = sjt_capture68;
        } else {
#line 321 "perf2.sj"
            sjt_capture66 = false;
        }

        if (sjt_capture66) {
            bool sjt_capture71;
            int32_t sjt_functionParam274;
            sjs_array_bool* sjt_parent73 = 0;

#line 7 "lib/common/array.sj"
            sjt_parent73 = &g_stateofdir;
#line 322 "perf2.sj"
            sjt_functionParam274 = 0;
#line 322
            sjf_array_bool_getat(sjt_parent73, sjt_functionParam274, &sjt_capture71);
            if (sjt_capture71) {
                int32_t sjt_functionParam275;
                bool sjt_functionParam276;
                sjs_array_bool* sjt_parent74 = 0;

#line 323 "perf2.sj"
                _parent->rotatey = _parent->rotatey + 0.05f;
#line 49 "lib/common/array.sj"
                sjt_parent74 = &g_stateofdir;
#line 324 "perf2.sj"
                sjt_functionParam275 = 0;
#line 324
                sjt_functionParam276 = _parent->rotatey < 7.0f;
#line 324
                sjf_array_bool_setat(sjt_parent74, sjt_functionParam275, sjt_functionParam276);
            } else {
                int32_t sjt_functionParam277;
                bool sjt_functionParam278;
                int32_t sjt_functionParam279;
                sjs_array_bool* sjt_parent75 = 0;
                sjs_array_bool* sjt_parent76 = 0;

#line 49 "lib/common/array.sj"
                sjt_parent75 = &g_stateof;
#line 326 "perf2.sj"
                sjt_functionParam277 = 0;
#line 7 "lib/common/array.sj"
                sjt_parent76 = &g_stateofdir;
#line 326 "perf2.sj"
                sjt_functionParam279 = 0;
#line 326
                sjf_array_bool_getat(sjt_parent76, sjt_functionParam279, &sjt_functionParam278);
#line 326
                sjf_array_bool_setat(sjt_parent75, sjt_functionParam277, sjt_functionParam278);
            }
        } else {
            bool sjt_capture72;
            bool sjt_capture73;
            int32_t sjt_functionParam280;
            sjs_array_bool* sjt_parent77 = 0;

#line 7 "lib/common/array.sj"
            sjt_parent77 = &g_stateof;
#line 328 "perf2.sj"
            sjt_functionParam280 = 1;
#line 328
            sjf_array_bool_getat(sjt_parent77, sjt_functionParam280, &sjt_capture73);
            if (sjt_capture73) {
                bool result18;
                bool sjt_capture74;
                bool sjt_capture75;
                int32_t sjt_functionParam281;
                sjs_array_bool* sjt_parent78 = 0;

#line 7 "lib/common/array.sj"
                sjt_parent78 = &g_stateof;
#line 328 "perf2.sj"
                sjt_functionParam281 = 0;
#line 328
                sjf_array_bool_getat(sjt_parent78, sjt_functionParam281, &sjt_capture75);
#line 328
                result18 = !sjt_capture75;
                if (result18) {
                    bool sjt_capture76;
                    int32_t sjt_functionParam282;
                    sjs_array_bool* sjt_parent79 = 0;

#line 7 "lib/common/array.sj"
                    sjt_parent79 = &g_stateof;
#line 328 "perf2.sj"
                    sjt_functionParam282 = 2;
#line 328
                    sjf_array_bool_getat(sjt_parent79, sjt_functionParam282, &sjt_capture76);
#line 328
                    sjt_capture74 = sjt_capture76;
                } else {
#line 328 "perf2.sj"
                    sjt_capture74 = false;
                }

#line 328
                sjt_capture72 = sjt_capture74;
            } else {
#line 328 "perf2.sj"
                sjt_capture72 = false;
            }

            if (sjt_capture72) {
                bool sjt_capture77;
                int32_t sjt_functionParam283;
                sjs_array_bool* sjt_parent80 = 0;

                if (_parent->rotatey > 0.0f) {
#line 329 "perf2.sj"
                    _parent->rotatey = _parent->rotatey - 0.05f;
                }

#line 7 "lib/common/array.sj"
                sjt_parent80 = &g_stateofdir;
#line 330 "perf2.sj"
                sjt_functionParam283 = 1;
#line 330
                sjf_array_bool_getat(sjt_parent80, sjt_functionParam283, &sjt_capture77);
                if (sjt_capture77) {
                    int32_t sjt_functionParam284;
                    bool sjt_functionParam285;
                    sjs_array_bool* sjt_parent81 = 0;

#line 331 "perf2.sj"
                    _parent->rotatex = _parent->rotatex + 0.05f;
#line 49 "lib/common/array.sj"
                    sjt_parent81 = &g_stateofdir;
#line 332 "perf2.sj"
                    sjt_functionParam284 = 1;
#line 332
                    sjt_functionParam285 = _parent->rotatex < 7.0f;
#line 332
                    sjf_array_bool_setat(sjt_parent81, sjt_functionParam284, sjt_functionParam285);
                } else {
                    int32_t sjt_functionParam286;
                    bool sjt_functionParam287;
                    int32_t sjt_functionParam288;
                    sjs_array_bool* sjt_parent82 = 0;
                    sjs_array_bool* sjt_parent83 = 0;

#line 49 "lib/common/array.sj"
                    sjt_parent82 = &g_stateof;
#line 334 "perf2.sj"
                    sjt_functionParam286 = 1;
#line 7 "lib/common/array.sj"
                    sjt_parent83 = &g_stateofdir;
#line 334 "perf2.sj"
                    sjt_functionParam288 = 1;
#line 334
                    sjf_array_bool_getat(sjt_parent83, sjt_functionParam288, &sjt_functionParam287);
#line 334
                    sjf_array_bool_setat(sjt_parent82, sjt_functionParam286, sjt_functionParam287);
                }
            }
        }

#line 7 "lib/common/array.sj"
        sjt_parent84 = &g_stateof;
#line 337 "perf2.sj"
        sjt_functionParam289 = 1;
#line 337
        sjf_array_bool_getat(sjt_parent84, sjt_functionParam289, &sjt_capture79);
#line 337
        result19 = !sjt_capture79;
        if (result19) {
            bool result20;
            bool sjt_capture80;
            bool sjt_capture81;
            int32_t sjt_functionParam290;
            sjs_array_bool* sjt_parent85 = 0;

#line 7 "lib/common/array.sj"
            sjt_parent85 = &g_stateof;
#line 337 "perf2.sj"
            sjt_functionParam290 = 0;
#line 337
            sjf_array_bool_getat(sjt_parent85, sjt_functionParam290, &sjt_capture81);
#line 337
            result20 = !sjt_capture81;
            if (result20) {
                bool sjt_capture82;
                int32_t sjt_functionParam291;
                sjs_array_bool* sjt_parent86 = 0;

#line 7 "lib/common/array.sj"
                sjt_parent86 = &g_stateof;
#line 337 "perf2.sj"
                sjt_functionParam291 = 2;
#line 337
                sjf_array_bool_getat(sjt_parent86, sjt_functionParam291, &sjt_capture82);
#line 337
                sjt_capture80 = sjt_capture82;
            } else {
#line 337 "perf2.sj"
                sjt_capture80 = false;
            }

#line 337
            sjt_capture78 = sjt_capture80;
        } else {
#line 337 "perf2.sj"
            sjt_capture78 = false;
        }

        if (sjt_capture78) {
            bool sjt_capture83;
            int32_t sjt_functionParam292;
            sjs_array_bool* sjt_parent87 = 0;

            if (_parent->rotatex > 0.0f) {
#line 338 "perf2.sj"
                _parent->rotatex = _parent->rotatex - 0.05f;
            }

#line 7 "lib/common/array.sj"
            sjt_parent87 = &g_stateofdir;
#line 339 "perf2.sj"
            sjt_functionParam292 = 2;
#line 339
            sjf_array_bool_getat(sjt_parent87, sjt_functionParam292, &sjt_capture83);
            if (sjt_capture83) {
                int32_t sjt_functionParam293;
                bool sjt_functionParam294;
                sjs_array_bool* sjt_parent88 = 0;

#line 340 "perf2.sj"
                _parent->rotatez = _parent->rotatez + 0.05f;
#line 49 "lib/common/array.sj"
                sjt_parent88 = &g_stateofdir;
#line 341 "perf2.sj"
                sjt_functionParam293 = 2;
#line 341
                sjt_functionParam294 = _parent->rotatez < 7.0f;
#line 341
                sjf_array_bool_setat(sjt_parent88, sjt_functionParam293, sjt_functionParam294);
            } else {
                bool result21;
                bool sjt_capture84;
                int32_t sjt_functionParam295;
                bool sjt_functionParam296;
                int32_t sjt_functionParam297;
                int32_t sjt_functionParam298;
                bool sjt_functionParam299;
                int32_t sjt_functionParam300;
                sjs_array_bool* sjt_parent89 = 0;
                sjs_array_bool* sjt_parent90 = 0;
                sjs_array_bool* sjt_parent91 = 0;
                sjs_array_bool* sjt_parent92 = 0;

#line 49 "lib/common/array.sj"
                sjt_parent89 = &g_stateof;
#line 343 "perf2.sj"
                sjt_functionParam295 = 2;
#line 7 "lib/common/array.sj"
                sjt_parent90 = &g_stateofdir;
#line 343 "perf2.sj"
                sjt_functionParam297 = 2;
#line 343
                sjf_array_bool_getat(sjt_parent90, sjt_functionParam297, &sjt_functionParam296);
#line 343
                sjf_array_bool_setat(sjt_parent89, sjt_functionParam295, sjt_functionParam296);
#line 49 "lib/common/array.sj"
                sjt_parent91 = &g_mainrot;
#line 344 "perf2.sj"
                sjt_functionParam298 = 0;
#line 7 "lib/common/array.sj"
                sjt_parent92 = &g_stateofdir;
#line 344 "perf2.sj"
                sjt_functionParam300 = 2;
#line 344
                sjf_array_bool_getat(sjt_parent92, sjt_functionParam300, &sjt_capture84);
#line 344
                result21 = !sjt_capture84;
#line 344
                sjt_functionParam299 = result21;
#line 344
                sjf_array_bool_setat(sjt_parent91, sjt_functionParam298, sjt_functionParam299);
            }
        }
    } else {
        bool result22;
        bool sjt_capture85;
        int32_t sjt_functionParam301;
        sjs_array_bool* sjt_parent93 = 0;

#line 7 "lib/common/array.sj"
        sjt_parent93 = &g_mainrot;
#line 348 "perf2.sj"
        sjt_functionParam301 = 1;
#line 348
        sjf_array_bool_getat(sjt_parent93, sjt_functionParam301, &sjt_capture85);
#line 348
        result22 = !sjt_capture85;
        if (result22) {
            bool sjt_capture86;
            int32_t sjt_functionParam302;
            sjs_array_bool* sjt_parent94 = 0;

#line 7 "lib/common/array.sj"
            sjt_parent94 = &g_stateofdir;
#line 349 "perf2.sj"
            sjt_functionParam302 = 0;
#line 349
            sjf_array_bool_getat(sjt_parent94, sjt_functionParam302, &sjt_capture86);
            if (sjt_capture86) {
                bool sjt_capture87;
                int32_t sjt_functionParam303;
                bool sjt_functionParam304;
                int32_t sjt_functionParam305;
                sjs_array_bool* sjt_parent95 = 0;
                sjs_array_bool* sjt_parent96 = 0;

#line 350 "perf2.sj"
                _parent->rotatey = _parent->rotatey + 0.05f;
#line 49 "lib/common/array.sj"
                sjt_parent95 = &g_stateofdir;
#line 351 "perf2.sj"
                sjt_functionParam303 = 0;
#line 351
                sjt_functionParam304 = _parent->rotatey < 7.0f;
#line 351
                sjf_array_bool_setat(sjt_parent95, sjt_functionParam303, sjt_functionParam304);
#line 7 "lib/common/array.sj"
                sjt_parent96 = &g_stateofdir;
#line 353 "perf2.sj"
                sjt_functionParam305 = 2;
#line 353
                sjf_array_bool_getat(sjt_parent96, sjt_functionParam305, &sjt_capture87);
                if (sjt_capture87) {
                    int32_t sjt_functionParam306;
                    bool sjt_functionParam307;
                    sjs_array_bool* sjt_parent97 = 0;

#line 354 "perf2.sj"
                    _parent->rotatez = _parent->rotatez + 0.05f;
#line 49 "lib/common/array.sj"
                    sjt_parent97 = &g_stateofdir;
#line 355 "perf2.sj"
                    sjt_functionParam306 = 2;
#line 355
                    sjt_functionParam307 = _parent->rotatez < 7.0f;
#line 355
                    sjf_array_bool_setat(sjt_parent97, sjt_functionParam306, sjt_functionParam307);
                } else {
                    float result23;
                    int32_t sjt_functionParam308;
                    bool sjt_functionParam309;
                    sjs_array_bool* sjt_parent98 = 0;

#line 357 "perf2.sj"
                    _parent->rotatez = _parent->rotatez - 0.05f;
#line 49 "lib/common/array.sj"
                    sjt_parent98 = &g_stateofdir;
#line 358 "perf2.sj"
                    sjt_functionParam308 = 2;
#line 358
                    result23 = -7.0f;
#line 358
                    sjt_functionParam309 = _parent->rotatez < result23;
#line 358
                    sjf_array_bool_setat(sjt_parent98, sjt_functionParam308, sjt_functionParam309);
                }
            } else {
                float result28;
                bool sjt_capture88;
                int32_t sjt_functionParam310;
                int32_t sjt_functionParam328;
                bool sjt_functionParam329;
                sjs_array_bool* sjt_parent110 = 0;
                sjs_array_bool* sjt_parent99 = 0;

#line 7 "lib/common/array.sj"
                sjt_parent99 = &g_stateofdir;
#line 361 "perf2.sj"
                sjt_functionParam310 = 1;
#line 361
                sjf_array_bool_getat(sjt_parent99, sjt_functionParam310, &sjt_capture88);
                if (sjt_capture88) {
                    bool sjt_capture89;
                    int32_t sjt_functionParam311;
                    bool sjt_functionParam312;
                    int32_t sjt_functionParam313;
                    sjs_array_bool* sjt_parent100 = 0;
                    sjs_array_bool* sjt_parent101 = 0;

#line 362 "perf2.sj"
                    _parent->rotatex = _parent->rotatex + 0.05f;
#line 49 "lib/common/array.sj"
                    sjt_parent100 = &g_stateofdir;
#line 363 "perf2.sj"
                    sjt_functionParam311 = 1;
#line 363
                    sjt_functionParam312 = _parent->rotatex < 7.0f;
#line 363
                    sjf_array_bool_setat(sjt_parent100, sjt_functionParam311, sjt_functionParam312);
#line 7 "lib/common/array.sj"
                    sjt_parent101 = &g_stateofdir;
#line 364 "perf2.sj"
                    sjt_functionParam313 = 2;
#line 364
                    sjf_array_bool_getat(sjt_parent101, sjt_functionParam313, &sjt_capture89);
                    if (sjt_capture89) {
                        int32_t sjt_functionParam314;
                        bool sjt_functionParam315;
                        sjs_array_bool* sjt_parent102 = 0;

#line 365 "perf2.sj"
                        _parent->rotatez = _parent->rotatez + 0.05f;
#line 49 "lib/common/array.sj"
                        sjt_parent102 = &g_stateofdir;
#line 366 "perf2.sj"
                        sjt_functionParam314 = 2;
#line 366
                        sjt_functionParam315 = _parent->rotatez < 7.0f;
#line 366
                        sjf_array_bool_setat(sjt_parent102, sjt_functionParam314, sjt_functionParam315);
                    } else {
                        float result24;
                        int32_t sjt_functionParam316;
                        bool sjt_functionParam317;
                        sjs_array_bool* sjt_parent103 = 0;

#line 368 "perf2.sj"
                        _parent->rotatez = _parent->rotatez - 0.05f;
#line 49 "lib/common/array.sj"
                        sjt_parent103 = &g_stateofdir;
#line 369 "perf2.sj"
                        sjt_functionParam316 = 2;
#line 369
                        result24 = -7.0f;
#line 369
                        sjt_functionParam317 = _parent->rotatez < result24;
#line 369
                        sjf_array_bool_setat(sjt_parent103, sjt_functionParam316, sjt_functionParam317);
                    }
                } else {
                    float result25;
                    bool sjt_capture90;
                    int32_t sjt_functionParam318;
                    bool sjt_functionParam319;
                    int32_t sjt_functionParam320;
                    sjs_array_bool* sjt_parent104 = 0;
                    sjs_array_bool* sjt_parent105 = 0;

#line 372 "perf2.sj"
                    _parent->rotatex = _parent->rotatex - 0.05f;
#line 49 "lib/common/array.sj"
                    sjt_parent104 = &g_stateofdir;
#line 373 "perf2.sj"
                    sjt_functionParam318 = 1;
#line 373
                    result25 = -7.0f;
#line 373
                    sjt_functionParam319 = _parent->rotatex < result25;
#line 373
                    sjf_array_bool_setat(sjt_parent104, sjt_functionParam318, sjt_functionParam319);
#line 7 "lib/common/array.sj"
                    sjt_parent105 = &g_stateofdir;
#line 374 "perf2.sj"
                    sjt_functionParam320 = 2;
#line 374
                    sjf_array_bool_getat(sjt_parent105, sjt_functionParam320, &sjt_capture90);
                    if (sjt_capture90) {
                        int32_t sjt_functionParam321;
                        bool sjt_functionParam322;
                        sjs_array_bool* sjt_parent106 = 0;

#line 375 "perf2.sj"
                        _parent->rotatez = _parent->rotatez + 0.05f;
#line 49 "lib/common/array.sj"
                        sjt_parent106 = &g_stateofdir;
#line 376 "perf2.sj"
                        sjt_functionParam321 = 2;
#line 376
                        sjt_functionParam322 = _parent->rotatez < 7.0f;
#line 376
                        sjf_array_bool_setat(sjt_parent106, sjt_functionParam321, sjt_functionParam322);
                        if (_parent->funcid != 18) {
                            bool result26;
                            bool sjt_capture91;
                            int32_t sjt_functionParam323;
                            bool sjt_functionParam324;
                            int32_t sjt_functionParam325;
                            sjs_array_bool* sjt_parent107 = 0;
                            sjs_array_bool* sjt_parent108 = 0;

#line 49 "lib/common/array.sj"
                            sjt_parent107 = &g_mainrot;
#line 377 "perf2.sj"
                            sjt_functionParam323 = 1;
#line 7 "lib/common/array.sj"
                            sjt_parent108 = &g_stateofdir;
#line 377 "perf2.sj"
                            sjt_functionParam325 = 2;
#line 377
                            sjf_array_bool_getat(sjt_parent108, sjt_functionParam325, &sjt_capture91);
#line 377
                            result26 = !sjt_capture91;
#line 377
                            sjt_functionParam324 = result26;
#line 377
                            sjf_array_bool_setat(sjt_parent107, sjt_functionParam323, sjt_functionParam324);
                        }
                    } else {
                        float result27;
                        int32_t sjt_functionParam326;
                        bool sjt_functionParam327;
                        sjs_array_bool* sjt_parent109 = 0;

#line 379 "perf2.sj"
                        _parent->rotatez = _parent->rotatez - 0.05f;
#line 49 "lib/common/array.sj"
                        sjt_parent109 = &g_stateofdir;
#line 380 "perf2.sj"
                        sjt_functionParam326 = 2;
#line 380
                        result27 = -7.0f;
#line 380
                        sjt_functionParam327 = _parent->rotatez < result27;
#line 380
                        sjf_array_bool_setat(sjt_parent109, sjt_functionParam326, sjt_functionParam327);
                    }
                }

#line 383
                _parent->rotatey = _parent->rotatey - 0.05f;
#line 49 "lib/common/array.sj"
                sjt_parent110 = &g_stateofdir;
#line 384 "perf2.sj"
                sjt_functionParam328 = 0;
#line 384
                result28 = -7.0f;
#line 384
                sjt_functionParam329 = _parent->rotatey < result28;
#line 384
                sjf_array_bool_setat(sjt_parent110, sjt_functionParam328, sjt_functionParam329);
            }
        }
    }

#line 7 "lib/common/array.sj"
    sjt_parent111 = &g_mainrot;
#line 388 "perf2.sj"
    sjt_functionParam330 = 0;
#line 388
    sjf_array_bool_getat(sjt_parent111, sjt_functionParam330, &sjt_capture93);
    if (sjt_capture93) {
        bool sjt_capture94;
        int32_t sjt_functionParam331;
        sjs_array_bool* sjt_parent112 = 0;

#line 7 "lib/common/array.sj"
        sjt_parent112 = &g_mainrot;
#line 388 "perf2.sj"
        sjt_functionParam331 = 1;
#line 388
        sjf_array_bool_getat(sjt_parent112, sjt_functionParam331, &sjt_capture94);
#line 388
        sjt_capture92 = sjt_capture94;
    } else {
#line 388 "perf2.sj"
        sjt_capture92 = false;
    }

    if (sjt_capture92) {
        if (_parent->rotatez > 0.0f) {
#line 390 "perf2.sj"
            _parent->rotatez = _parent->rotatez - 0.1f;
        } else {
            int32_t sjt_functionParam332;
            bool sjt_functionParam333;
            int32_t sjt_functionParam334;
            bool sjt_functionParam335;
            int32_t sjt_functionParam336;
            bool sjt_functionParam337;
            int32_t sjt_functionParam338;
            bool sjt_functionParam339;
            int32_t sjt_functionParam340;
            bool sjt_functionParam341;
            int32_t sjt_functionParam342;
            bool sjt_functionParam343;
            int32_t sjt_functionParam344;
            bool sjt_functionParam345;
            int32_t sjt_functionParam346;
            bool sjt_functionParam347;
            sjs_array_bool* sjt_parent113 = 0;
            sjs_array_bool* sjt_parent114 = 0;
            sjs_array_bool* sjt_parent115 = 0;
            sjs_array_bool* sjt_parent116 = 0;
            sjs_array_bool* sjt_parent117 = 0;
            sjs_array_bool* sjt_parent118 = 0;
            sjs_array_bool* sjt_parent119 = 0;
            sjs_array_bool* sjt_parent120 = 0;

#line 393 "perf2.sj"
            _parent->rotatez = 0.0f;
#line 394
            _parent->rotatex = 0.0f;
#line 395
            _parent->rotatey = 0.0f;
#line 49 "lib/common/array.sj"
            sjt_parent113 = &g_stateof;
#line 396 "perf2.sj"
            sjt_functionParam332 = 0;
#line 396
            sjt_functionParam333 = true;
#line 396
            sjf_array_bool_setat(sjt_parent113, sjt_functionParam332, sjt_functionParam333);
#line 49 "lib/common/array.sj"
            sjt_parent114 = &g_stateof;
#line 397 "perf2.sj"
            sjt_functionParam334 = 1;
#line 397
            sjt_functionParam335 = true;
#line 397
            sjf_array_bool_setat(sjt_parent114, sjt_functionParam334, sjt_functionParam335);
#line 49 "lib/common/array.sj"
            sjt_parent115 = &g_stateof;
#line 398 "perf2.sj"
            sjt_functionParam336 = 2;
#line 398
            sjt_functionParam337 = true;
#line 398
            sjf_array_bool_setat(sjt_parent115, sjt_functionParam336, sjt_functionParam337);
#line 49 "lib/common/array.sj"
            sjt_parent116 = &g_stateofdir;
#line 399 "perf2.sj"
            sjt_functionParam338 = 0;
#line 399
            sjt_functionParam339 = true;
#line 399
            sjf_array_bool_setat(sjt_parent116, sjt_functionParam338, sjt_functionParam339);
#line 49 "lib/common/array.sj"
            sjt_parent117 = &g_stateofdir;
#line 400 "perf2.sj"
            sjt_functionParam340 = 1;
#line 400
            sjt_functionParam341 = true;
#line 400
            sjf_array_bool_setat(sjt_parent117, sjt_functionParam340, sjt_functionParam341);
#line 49 "lib/common/array.sj"
            sjt_parent118 = &g_stateofdir;
#line 401 "perf2.sj"
            sjt_functionParam342 = 2;
#line 401
            sjt_functionParam343 = true;
#line 401
            sjf_array_bool_setat(sjt_parent118, sjt_functionParam342, sjt_functionParam343);
#line 49 "lib/common/array.sj"
            sjt_parent119 = &g_mainrot;
#line 402 "perf2.sj"
            sjt_functionParam344 = 0;
#line 402
            sjt_functionParam345 = false;
#line 402
            sjf_array_bool_setat(sjt_parent119, sjt_functionParam344, sjt_functionParam345);
#line 49 "lib/common/array.sj"
            sjt_parent120 = &g_mainrot;
#line 403 "perf2.sj"
            sjt_functionParam346 = 1;
#line 403
            sjt_functionParam347 = false;
#line 403
            sjf_array_bool_setat(sjt_parent120, sjt_functionParam346, sjt_functionParam347);
#line 404
            _parent->funcid = _parent->funcid + 1;
        }
    }
}

void sjf_test_firemouseevent(sjs_test* _parent, sjs_mouseevent* mouseevent, bool* _return) {
#line 119 "perf2.sj"
    (*_return) = true;
}

void sjf_test_getclasstype(sjs_object* _this, int* _return) {
    *_return = 91;
}

void sjf_test_getrect(sjs_test* _parent, sjs_rect* _return) {
    _return->_refCount = 1;
#line 87 "perf2.sj"
    sjf_rect_copy(_return, &_parent->_rect);
}

void sjf_test_getrect_heap(sjs_test* _parent, sjs_rect** _return) {
    (*_return) = (sjs_rect*)malloc(sizeof(sjs_rect));
    (*_return)->_refCount = 1;
#line 87 "perf2.sj"
    sjf_rect_copy((*_return), &_parent->_rect);
}

void sjf_test_getsize(sjs_test* _parent, sjs_size* maxsize, sjs_size* _return) {
    _return->_refCount = 1;
#line 84 "perf2.sj"
    _return->w = maxsize->w;
#line 84
    _return->h = maxsize->h;
#line 84
    sjf_size(_return);
}

void sjf_test_getsize_heap(sjs_test* _parent, sjs_size* maxsize, sjs_size** _return) {
    (*_return) = (sjs_size*)malloc(sizeof(sjs_size));
    (*_return)->_refCount = 1;
#line 84 "perf2.sj"
    (*_return)->w = maxsize->w;
#line 84
    (*_return)->h = maxsize->h;
#line 84
    sjf_size_heap((*_return));
}

void sjf_test_gett(sjs_test* _parent, int32_t xpi, int32_t n, float* _return) {
    int32_t sjt_cast11;
    int32_t sjt_cast12;
    int32_t sjt_cast13;

#line 411 "perf2.sj"
    sjt_cast11 = xpi;
#line 411
    sjt_cast12 = n;
#line 412
    sjt_cast13 = g_dotsscale;
#line 412
    (*_return) = (float)sjt_cast11 * ((float)sjt_cast12 / (float)sjt_cast13);
}

void sjf_test_gettm(sjs_test* _parent, int32_t xpi, int32_t n, float* _return) {
    float result4;
    int32_t sjt_cast10;
    int32_t sjt_cast7;
    int32_t sjt_cast8;
    int32_t sjt_cast9;

#line 416 "perf2.sj"
    sjt_cast7 = xpi;
#line 417
    result4 = -1.0f;
#line 416
    sjt_cast8 = xpi;
#line 416
    sjt_cast9 = n;
#line 417
    sjt_cast10 = g_dotsscale;
#line 417
    (*_return) = ((float)sjt_cast7 * (result4 * g_f32_pi)) + (((float)sjt_cast8 * 2.0f) * ((float)sjt_cast9 / (float)sjt_cast10));
}

void sjf_test_heap(sjs_test* _this) {
}

void sjf_test_img_gettm(sjs_test* _parent, int32_t xpi, int32_t n, float* _return) {
    float result5;
    int32_t sjt_cast14;
    int32_t sjt_cast15;
    int32_t sjt_cast16;
    int32_t sjt_cast17;

#line 421 "perf2.sj"
    sjt_cast14 = xpi;
#line 422
    result5 = -1.0f;
#line 421
    sjt_cast15 = xpi;
#line 421
    sjt_cast16 = n;
#line 422
    sjt_cast17 = g_img_dotsscale;
#line 422
    (*_return) = ((float)sjt_cast14 * (result5 * g_f32_pi)) + (((float)sjt_cast15 * 2.0f) * ((float)sjt_cast16 / (float)sjt_cast17));
}

void sjf_test_imgdata_functionlist(sjs_test* _parent) {
    int32_t n;
    int32_t sjt_forEnd19;
    int32_t sjt_forStart19;

#line 426 "perf2.sj"
    sjt_forStart19 = 0;
#line 426
    sjt_forEnd19 = g_img_dots;
#line 426
    n = sjt_forStart19;
    while (n < sjt_forEnd19) {
        float result10;
        float result11;
        float result12;
        float result13;
        float result14;
        float result15;
        float result16;
        float result6;
        float result7;
        float result8;
        float result9;
        int32_t sjt_functionParam228;
        int32_t sjt_functionParam229;
        int32_t sjt_functionParam230;
        float sjt_functionParam231;
        int32_t sjt_functionParam232;
        float sjt_functionParam233;
        int32_t sjt_functionParam234;
        float sjt_functionParam235;
        int32_t sjt_functionParam236;
        float sjt_functionParam237;
        int32_t sjt_functionParam238;
        float sjt_functionParam239;
        int32_t sjt_functionParam240;
        float sjt_functionParam241;
        int32_t sjt_functionParam242;
        float sjt_functionParam243;
        int32_t sjt_functionParam244;
        float sjt_functionParam245;
        int32_t sjt_functionParam246;
        float sjt_functionParam247;
        int32_t sjt_functionParam248;
        float sjt_functionParam249;
        int32_t sjt_functionParam250;
        float sjt_functionParam251;
        int32_t sjt_functionParam252;
        float sjt_functionParam253;
        int32_t sjt_functionParam254;
        float sjt_functionParam255;
        int32_t sjt_functionParam256;
        float sjt_functionParam257;
        int32_t sjt_functionParam258;
        float sjt_functionParam259;
        int32_t sjt_functionParam260;
        float sjt_functionParam261;
        int32_t sjt_functionParam262;
        float sjt_functionParam263;
        int32_t sjt_functionParam264;
        float sjt_functionParam265;
        int32_t sjt_functionParam266;
        float sjt_functionParam267;
        int32_t sjt_functionParam268;
        float sjt_functionParam269;
        sjs_array_f32* sjt_parent49 = 0;
        sjs_array_f32* sjt_parent50 = 0;
        sjs_array_f32* sjt_parent51 = 0;
        sjs_array_f32* sjt_parent52 = 0;
        sjs_array_f32* sjt_parent53 = 0;
        sjs_array_f32* sjt_parent54 = 0;
        sjs_array_f32* sjt_parent55 = 0;
        sjs_array_f32* sjt_parent56 = 0;
        sjs_array_f32* sjt_parent57 = 0;
        sjs_array_f32* sjt_parent58 = 0;
        sjs_array_f32* sjt_parent59 = 0;
        sjs_array_f32* sjt_parent60 = 0;
        sjs_array_f32* sjt_parent61 = 0;
        sjs_array_f32* sjt_parent62 = 0;
        sjs_array_f32* sjt_parent63 = 0;
        sjs_array_f32* sjt_parent64 = 0;
        sjs_array_f32* sjt_parent65 = 0;
        sjs_array_f32* sjt_parent66 = 0;
        sjs_array_f32* sjt_parent67 = 0;
        sjs_array_f32* sjt_parent68 = 0;
        float t;

#line 427 "perf2.sj"
        sjt_functionParam228 = 1;
#line 426
        sjt_functionParam229 = n;
#line 426
        sjf_test_img_gettm(_parent, sjt_functionParam228, sjt_functionParam229, &t);
#line 49 "lib/common/array.sj"
        sjt_parent49 = &_parent->datavert1x;
#line 426 "perf2.sj"
        sjt_functionParam230 = n;
#line 428
        result6 = -3.0f;
#line 428
        sjt_functionParam231 = result6 + ((t * 0.98f) / 3.0f);
#line 428
        sjf_array_f32_setat(sjt_parent49, sjt_functionParam230, sjt_functionParam231);
#line 49 "lib/common/array.sj"
        sjt_parent50 = &_parent->datavert1y;
#line 426 "perf2.sj"
        sjt_functionParam232 = n;
#line 429
        sjt_functionParam233 = t * 0.98f;
#line 429
        sjf_array_f32_setat(sjt_parent50, sjt_functionParam232, sjt_functionParam233);
#line 49 "lib/common/array.sj"
        sjt_parent51 = &_parent->datavert2x;
#line 426 "perf2.sj"
        sjt_functionParam234 = n;
#line 430
        result7 = -2.0f;
#line 430
        sjt_functionParam235 = (result7 - (2.0f / 3.0f)) + ((t / g_f32_pi) / 3.0f);
#line 430
        sjf_array_f32_setat(sjt_parent51, sjt_functionParam234, sjt_functionParam235);
#line 49 "lib/common/array.sj"
        sjt_parent52 = &_parent->datavert2y;
#line 426 "perf2.sj"
        sjt_functionParam236 = n;
#line 431
        sjt_functionParam237 = (t / g_f32_pi) - 2.0f;
#line 431
        sjf_array_f32_setat(sjt_parent52, sjt_functionParam236, sjt_functionParam237);
#line 49 "lib/common/array.sj"
        sjt_parent53 = &_parent->datavert3x;
#line 426 "perf2.sj"
        sjt_functionParam238 = n;
#line 432
        result8 = -1.0f;
#line 432
        sjt_functionParam239 = (result8 - (2.0f / 3.0f)) + ((t / g_f32_pi) / 3.0f);
#line 432
        sjf_array_f32_setat(sjt_parent53, sjt_functionParam238, sjt_functionParam239);
#line 49 "lib/common/array.sj"
        sjt_parent54 = &_parent->datavert3y;
#line 426 "perf2.sj"
        sjt_functionParam240 = n;
#line 433
        sjt_functionParam241 = (t / g_f32_pi) + 1.0f;
#line 433
        sjf_array_f32_setat(sjt_parent54, sjt_functionParam240, sjt_functionParam241);
#line 49 "lib/common/array.sj"
        sjt_parent55 = &_parent->datavert4x;
#line 426 "perf2.sj"
        sjt_functionParam242 = n;
#line 434
        result9 = -2.0f;
#line 434
        sjt_functionParam243 = (result9 / 3.0f) + ((t / g_f32_pi) / 3.0f);
#line 434
        sjf_array_f32_setat(sjt_parent55, sjt_functionParam242, sjt_functionParam243);
#line 49 "lib/common/array.sj"
        sjt_parent56 = &_parent->datavert4y;
#line 426 "perf2.sj"
        sjt_functionParam244 = n;
#line 435
        sjt_functionParam245 = 1.0f + (t / g_f32_pi);
#line 435
        sjf_array_f32_setat(sjt_parent56, sjt_functionParam244, sjt_functionParam245);
#line 49 "lib/common/array.sj"
        sjt_parent57 = &_parent->datavert5x;
#line 426 "perf2.sj"
        sjt_functionParam246 = n;
#line 436
        sjt_functionParam247 = (1.0f / 3.0f) + (((t / g_f32_pi) * 2.0f) / 3.0f);
#line 436
        sjf_array_f32_setat(sjt_parent57, sjt_functionParam246, sjt_functionParam247);
#line 49 "lib/common/array.sj"
        sjt_parent58 = &_parent->datavert5y;
#line 426 "perf2.sj"
        sjt_functionParam248 = n;
#line 437
        sjt_functionParam249 = 1.0f + ((t / g_f32_pi) * 2.0f);
#line 437
        sjf_array_f32_setat(sjt_parent58, sjt_functionParam248, sjt_functionParam249);
#line 49 "lib/common/array.sj"
        sjt_parent59 = &_parent->datahotizont1x;
#line 426 "perf2.sj"
        sjt_functionParam250 = n;
#line 440
        result10 = -3.5f;
#line 440
        sjt_functionParam251 = result10 + (t / 7.0f);
#line 440
        sjf_array_f32_setat(sjt_parent59, sjt_functionParam250, sjt_functionParam251);
#line 49 "lib/common/array.sj"
        sjt_parent60 = &_parent->datahotizont1y;
#line 426 "perf2.sj"
        sjt_functionParam252 = n;
#line 441
        result11 = -3.0f;
#line 441
        sjt_functionParam253 = result11;
#line 441
        sjf_array_f32_setat(sjt_parent60, sjt_functionParam252, sjt_functionParam253);
#line 49 "lib/common/array.sj"
        sjt_parent61 = &_parent->datahotizont2x;
#line 426 "perf2.sj"
        sjt_functionParam254 = n;
#line 442
        result12 = -1.0f;
#line 442
        sjt_functionParam255 = (result12 - (1.0f / 3.0f)) + (t / g_f32_pi);
#line 442
        sjf_array_f32_setat(sjt_parent61, sjt_functionParam254, sjt_functionParam255);
#line 49 "lib/common/array.sj"
        sjt_parent62 = &_parent->datahotizont2y;
#line 426 "perf2.sj"
        sjt_functionParam256 = n;
#line 443
        result13 = -1.0f;
#line 443
        sjt_functionParam257 = result13;
#line 443
        sjf_array_f32_setat(sjt_parent62, sjt_functionParam256, sjt_functionParam257);
#line 49 "lib/common/array.sj"
        sjt_parent63 = &_parent->datahotizont3x;
#line 426 "perf2.sj"
        sjt_functionParam258 = n;
#line 444
        result14 = -1.5f;
#line 444
        sjt_functionParam259 = result14 + ((t / g_f32_pi) / 2.0f);
#line 444
        sjf_array_f32_setat(sjt_parent63, sjt_functionParam258, sjt_functionParam259);
#line 49 "lib/common/array.sj"
        sjt_parent64 = &_parent->datahotizont3y;
#line 426 "perf2.sj"
        sjt_functionParam260 = n;
#line 445
        sjt_functionParam261 = 0.0f;
#line 445
        sjf_array_f32_setat(sjt_parent64, sjt_functionParam260, sjt_functionParam261);
#line 49 "lib/common/array.sj"
        sjt_parent65 = &_parent->datahotizont4x;
#line 426 "perf2.sj"
        sjt_functionParam262 = n;
#line 446
        result15 = -0.8f;
#line 446
        sjt_functionParam263 = result15 + ((t / g_f32_pi) / 2.0f);
#line 446
        sjf_array_f32_setat(sjt_parent65, sjt_functionParam262, sjt_functionParam263);
#line 49 "lib/common/array.sj"
        sjt_parent66 = &_parent->datahotizont4y;
#line 426 "perf2.sj"
        sjt_functionParam264 = n;
#line 447
        sjt_functionParam265 = 2.0f;
#line 447
        sjf_array_f32_setat(sjt_parent66, sjt_functionParam264, sjt_functionParam265);
#line 49 "lib/common/array.sj"
        sjt_parent67 = &_parent->datahotizont5x;
#line 426 "perf2.sj"
        sjt_functionParam266 = n;
#line 448
        result16 = -1.0f;
#line 448
        sjt_functionParam267 = (result16 / 2.0f) + ((t / g_f32_pi) * (2.0f - (1.0f / 2.0f)));
#line 448
        sjf_array_f32_setat(sjt_parent67, sjt_functionParam266, sjt_functionParam267);
#line 49 "lib/common/array.sj"
        sjt_parent68 = &_parent->datahotizont5y;
#line 426 "perf2.sj"
        sjt_functionParam268 = n;
#line 449
        sjt_functionParam269 = 3.0f;
#line 449
        sjf_array_f32_setat(sjt_parent68, sjt_functionParam268, sjt_functionParam269);
#line 426
        n++;
    }
}

void sjf_test_render(sjs_test* _parent, sjs_scene2d* scene) {
    float r;
    bool sjt_while1;

    sjf_test_calculate(_parent);
    sjf_test_findaxis(_parent);
#line 126 "perf2.sj"
    glLoadIdentity();
#line 127
    glTranslatef(0.0f, 0.0f, -7.0f);
#line 130
    r = 0.0f;
#line 131
    sjt_while1 = r < 360.0f;
    while (sjt_while1) {
        int32_t n;
        int32_t sjt_forEnd20;
        int32_t sjt_forStart20;
        float sjt_functionParam348;
        float sjt_functionParam349;
        float sjt_functionParam350;
        float sjt_functionParam351;
        float sjt_functionParam352;
        float sjt_functionParam353;
        float sjt_functionParam354;

        if (_parent->rotatex > 0.0f) {
#line 132 "perf2.sj"
            sjt_functionParam348 = _parent->rotatex;
        } else {
            float result29;

#line 133 "perf2.sj"
            result29 = -1.0f;
#line 133
            sjt_functionParam348 = (result29 * _parent->rotatex) / 14.0f;
        }

        if (_parent->rotatey > 0.0f) {
#line 132 "perf2.sj"
            sjt_functionParam349 = _parent->rotatey;
        } else {
            float result30;

#line 134 "perf2.sj"
            result30 = -1.0f;
#line 134
            sjt_functionParam349 = (result30 * _parent->rotatey) / 14.0f;
        }

        if (_parent->rotatez > 0.0f) {
#line 132 "perf2.sj"
            sjt_functionParam350 = _parent->rotatez;
        } else {
            float result31;

#line 135 "perf2.sj"
            result31 = -1.0f;
#line 135
            sjt_functionParam350 = (result31 * _parent->rotatez) / 14.0f;
        }

        sjf_glcolor3f(sjt_functionParam348, sjt_functionParam349, sjt_functionParam350);
#line 138 "perf2.sj"
        sjt_functionParam351 = r / (100.0f / g_rotateradius);
#line 138
        sjt_functionParam352 = _parent->rotatex;
#line 138
        sjt_functionParam353 = _parent->rotatey;
#line 138
        sjt_functionParam354 = _parent->rotatez;
#line 138
        sjf_glrotated(sjt_functionParam351, sjt_functionParam352, sjt_functionParam353, sjt_functionParam354);
#line 138
        sjf_glbeginpoints();
#line 140
        sjt_forStart20 = 0;
#line 140
        sjt_forEnd20 = g_dots;
#line 140
        n = sjt_forStart20;
        while (n < sjt_forEnd20) {
            if (_parent->funcid == 18) {
                if (n < g_img_dots) {
                    float sjt_capture100;
                    float sjt_capture101;
                    float sjt_capture102;
                    float sjt_capture103;
                    float sjt_capture104;
                    float sjt_capture105;
                    float sjt_capture106;
                    float sjt_capture107;
                    float sjt_capture108;
                    float sjt_capture109;
                    float sjt_capture110;
                    float sjt_capture111;
                    float sjt_capture112;
                    float sjt_capture113;
                    float sjt_capture114;
                    float sjt_capture115;
                    float sjt_capture116;
                    float sjt_capture117;
                    float sjt_capture118;
                    float sjt_capture119;
                    float sjt_capture120;
                    float sjt_capture121;
                    float sjt_capture122;
                    float sjt_capture123;
                    float sjt_capture124;
                    float sjt_capture125;
                    float sjt_capture126;
                    float sjt_capture127;
                    float sjt_capture128;
                    float sjt_capture129;
                    float sjt_capture130;
                    float sjt_capture131;
                    float sjt_capture132;
                    float sjt_capture133;
                    float sjt_capture134;
                    float sjt_capture95;
                    float sjt_capture96;
                    float sjt_capture97;
                    float sjt_capture98;
                    float sjt_capture99;
                    float sjt_functionParam355;
                    int32_t sjt_functionParam356;
                    float sjt_functionParam357;
                    int32_t sjt_functionParam358;
                    float sjt_functionParam359;
                    float sjt_functionParam360;
                    int32_t sjt_functionParam361;
                    float sjt_functionParam362;
                    int32_t sjt_functionParam363;
                    float sjt_functionParam364;
                    float sjt_functionParam365;
                    int32_t sjt_functionParam366;
                    float sjt_functionParam367;
                    int32_t sjt_functionParam368;
                    float sjt_functionParam369;
                    float sjt_functionParam370;
                    int32_t sjt_functionParam371;
                    float sjt_functionParam372;
                    int32_t sjt_functionParam373;
                    float sjt_functionParam374;
                    float sjt_functionParam375;
                    int32_t sjt_functionParam376;
                    float sjt_functionParam377;
                    int32_t sjt_functionParam378;
                    float sjt_functionParam379;
                    float sjt_functionParam380;
                    int32_t sjt_functionParam381;
                    float sjt_functionParam382;
                    int32_t sjt_functionParam383;
                    float sjt_functionParam384;
                    float sjt_functionParam385;
                    int32_t sjt_functionParam386;
                    float sjt_functionParam387;
                    int32_t sjt_functionParam388;
                    float sjt_functionParam389;
                    float sjt_functionParam390;
                    int32_t sjt_functionParam391;
                    float sjt_functionParam392;
                    int32_t sjt_functionParam393;
                    float sjt_functionParam394;
                    float sjt_functionParam395;
                    int32_t sjt_functionParam396;
                    float sjt_functionParam397;
                    int32_t sjt_functionParam398;
                    float sjt_functionParam399;
                    float sjt_functionParam400;
                    int32_t sjt_functionParam401;
                    float sjt_functionParam402;
                    int32_t sjt_functionParam403;
                    float sjt_functionParam404;
                    float sjt_functionParam405;
                    int32_t sjt_functionParam406;
                    float sjt_functionParam407;
                    int32_t sjt_functionParam408;
                    float sjt_functionParam409;
                    float sjt_functionParam410;
                    int32_t sjt_functionParam411;
                    float sjt_functionParam412;
                    int32_t sjt_functionParam413;
                    float sjt_functionParam414;
                    float sjt_functionParam415;
                    int32_t sjt_functionParam416;
                    float sjt_functionParam417;
                    int32_t sjt_functionParam418;
                    float sjt_functionParam419;
                    float sjt_functionParam420;
                    int32_t sjt_functionParam421;
                    float sjt_functionParam422;
                    int32_t sjt_functionParam423;
                    float sjt_functionParam424;
                    float sjt_functionParam425;
                    int32_t sjt_functionParam426;
                    float sjt_functionParam427;
                    int32_t sjt_functionParam428;
                    float sjt_functionParam429;
                    float sjt_functionParam430;
                    int32_t sjt_functionParam431;
                    float sjt_functionParam432;
                    int32_t sjt_functionParam433;
                    float sjt_functionParam434;
                    float sjt_functionParam435;
                    int32_t sjt_functionParam436;
                    float sjt_functionParam437;
                    int32_t sjt_functionParam438;
                    float sjt_functionParam439;
                    float sjt_functionParam440;
                    int32_t sjt_functionParam441;
                    float sjt_functionParam442;
                    int32_t sjt_functionParam443;
                    float sjt_functionParam444;
                    float sjt_functionParam445;
                    int32_t sjt_functionParam446;
                    float sjt_functionParam447;
                    int32_t sjt_functionParam448;
                    float sjt_functionParam449;
                    float sjt_functionParam450;
                    int32_t sjt_functionParam451;
                    float sjt_functionParam452;
                    int32_t sjt_functionParam453;
                    float sjt_functionParam454;
                    sjs_array_f32* sjt_parent121 = 0;
                    sjs_array_f32* sjt_parent122 = 0;
                    sjs_array_f32* sjt_parent123 = 0;
                    sjs_array_f32* sjt_parent124 = 0;
                    sjs_array_f32* sjt_parent125 = 0;
                    sjs_array_f32* sjt_parent126 = 0;
                    sjs_array_f32* sjt_parent127 = 0;
                    sjs_array_f32* sjt_parent128 = 0;
                    sjs_array_f32* sjt_parent129 = 0;
                    sjs_array_f32* sjt_parent130 = 0;
                    sjs_array_f32* sjt_parent131 = 0;
                    sjs_array_f32* sjt_parent132 = 0;
                    sjs_array_f32* sjt_parent133 = 0;
                    sjs_array_f32* sjt_parent134 = 0;
                    sjs_array_f32* sjt_parent135 = 0;
                    sjs_array_f32* sjt_parent136 = 0;
                    sjs_array_f32* sjt_parent137 = 0;
                    sjs_array_f32* sjt_parent138 = 0;
                    sjs_array_f32* sjt_parent139 = 0;
                    sjs_array_f32* sjt_parent140 = 0;
                    sjs_array_f32* sjt_parent141 = 0;
                    sjs_array_f32* sjt_parent142 = 0;
                    sjs_array_f32* sjt_parent143 = 0;
                    sjs_array_f32* sjt_parent144 = 0;
                    sjs_array_f32* sjt_parent145 = 0;
                    sjs_array_f32* sjt_parent146 = 0;
                    sjs_array_f32* sjt_parent147 = 0;
                    sjs_array_f32* sjt_parent148 = 0;
                    sjs_array_f32* sjt_parent149 = 0;
                    sjs_array_f32* sjt_parent150 = 0;
                    sjs_array_f32* sjt_parent151 = 0;
                    sjs_array_f32* sjt_parent152 = 0;
                    sjs_array_f32* sjt_parent153 = 0;
                    sjs_array_f32* sjt_parent154 = 0;
                    sjs_array_f32* sjt_parent155 = 0;
                    sjs_array_f32* sjt_parent156 = 0;
                    sjs_array_f32* sjt_parent157 = 0;
                    sjs_array_f32* sjt_parent158 = 0;
                    sjs_array_f32* sjt_parent159 = 0;
                    sjs_array_f32* sjt_parent160 = 0;

#line 7 "lib/common/array.sj"
                    sjt_parent121 = &_parent->datahotizont1x;
#line 140 "perf2.sj"
                    sjt_functionParam356 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent121, sjt_functionParam356, &sjt_capture95);
#line 143
                    sjt_functionParam355 = sjt_capture95 * g_scale;
#line 7 "lib/common/array.sj"
                    sjt_parent122 = &_parent->datahotizont1y;
#line 140 "perf2.sj"
                    sjt_functionParam358 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent122, sjt_functionParam358, &sjt_capture96);
#line 143
                    sjt_functionParam357 = sjt_capture96 * g_scale;
#line 143
                    sjt_functionParam359 = 0.0f;
#line 143
                    sjf_glvertex3f(sjt_functionParam355, sjt_functionParam357, sjt_functionParam359);
#line 7 "lib/common/array.sj"
                    sjt_parent123 = &_parent->datahotizont2x;
#line 140 "perf2.sj"
                    sjt_functionParam361 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent123, sjt_functionParam361, &sjt_capture97);
#line 144
                    sjt_functionParam360 = sjt_capture97 * g_scale;
#line 7 "lib/common/array.sj"
                    sjt_parent124 = &_parent->datahotizont2y;
#line 140 "perf2.sj"
                    sjt_functionParam363 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent124, sjt_functionParam363, &sjt_capture98);
#line 144
                    sjt_functionParam362 = sjt_capture98 * g_scale;
#line 144
                    sjt_functionParam364 = 0.0f;
#line 144
                    sjf_glvertex3f(sjt_functionParam360, sjt_functionParam362, sjt_functionParam364);
#line 7 "lib/common/array.sj"
                    sjt_parent125 = &_parent->datahotizont3x;
#line 140 "perf2.sj"
                    sjt_functionParam366 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent125, sjt_functionParam366, &sjt_capture99);
#line 145
                    sjt_functionParam365 = sjt_capture99 * g_scale;
#line 7 "lib/common/array.sj"
                    sjt_parent126 = &_parent->datahotizont3y;
#line 140 "perf2.sj"
                    sjt_functionParam368 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent126, sjt_functionParam368, &sjt_capture100);
#line 145
                    sjt_functionParam367 = sjt_capture100 * g_scale;
#line 145
                    sjt_functionParam369 = 0.0f;
#line 145
                    sjf_glvertex3f(sjt_functionParam365, sjt_functionParam367, sjt_functionParam369);
#line 7 "lib/common/array.sj"
                    sjt_parent127 = &_parent->datahotizont4x;
#line 140 "perf2.sj"
                    sjt_functionParam371 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent127, sjt_functionParam371, &sjt_capture101);
#line 146
                    sjt_functionParam370 = sjt_capture101 * g_scale;
#line 7 "lib/common/array.sj"
                    sjt_parent128 = &_parent->datahotizont4y;
#line 140 "perf2.sj"
                    sjt_functionParam373 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent128, sjt_functionParam373, &sjt_capture102);
#line 146
                    sjt_functionParam372 = sjt_capture102 * g_scale;
#line 146
                    sjt_functionParam374 = 0.0f;
#line 146
                    sjf_glvertex3f(sjt_functionParam370, sjt_functionParam372, sjt_functionParam374);
#line 7 "lib/common/array.sj"
                    sjt_parent129 = &_parent->datahotizont5x;
#line 140 "perf2.sj"
                    sjt_functionParam376 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent129, sjt_functionParam376, &sjt_capture103);
#line 147
                    sjt_functionParam375 = sjt_capture103 * g_scale;
#line 7 "lib/common/array.sj"
                    sjt_parent130 = &_parent->datahotizont5y;
#line 140 "perf2.sj"
                    sjt_functionParam378 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent130, sjt_functionParam378, &sjt_capture104);
#line 147
                    sjt_functionParam377 = sjt_capture104 * g_scale;
#line 147
                    sjt_functionParam379 = 0.0f;
#line 147
                    sjf_glvertex3f(sjt_functionParam375, sjt_functionParam377, sjt_functionParam379);
#line 7 "lib/common/array.sj"
                    sjt_parent131 = &_parent->datavert1x;
#line 140 "perf2.sj"
                    sjt_functionParam381 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent131, sjt_functionParam381, &sjt_capture105);
#line 149
                    sjt_functionParam380 = sjt_capture105 * g_scale;
#line 7 "lib/common/array.sj"
                    sjt_parent132 = &_parent->datavert1y;
#line 140 "perf2.sj"
                    sjt_functionParam383 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent132, sjt_functionParam383, &sjt_capture106);
#line 149
                    sjt_functionParam382 = sjt_capture106 * g_scale;
#line 149
                    sjt_functionParam384 = 0.0f;
#line 149
                    sjf_glvertex3f(sjt_functionParam380, sjt_functionParam382, sjt_functionParam384);
#line 7 "lib/common/array.sj"
                    sjt_parent133 = &_parent->datavert2x;
#line 140 "perf2.sj"
                    sjt_functionParam386 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent133, sjt_functionParam386, &sjt_capture107);
#line 150
                    sjt_functionParam385 = sjt_capture107 * g_scale;
#line 7 "lib/common/array.sj"
                    sjt_parent134 = &_parent->datavert2y;
#line 140 "perf2.sj"
                    sjt_functionParam388 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent134, sjt_functionParam388, &sjt_capture108);
#line 150
                    sjt_functionParam387 = sjt_capture108 * g_scale;
#line 150
                    sjt_functionParam389 = 0.0f;
#line 150
                    sjf_glvertex3f(sjt_functionParam385, sjt_functionParam387, sjt_functionParam389);
#line 7 "lib/common/array.sj"
                    sjt_parent135 = &_parent->datavert3x;
#line 140 "perf2.sj"
                    sjt_functionParam391 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent135, sjt_functionParam391, &sjt_capture109);
#line 151
                    sjt_functionParam390 = sjt_capture109 * g_scale;
#line 7 "lib/common/array.sj"
                    sjt_parent136 = &_parent->datavert3y;
#line 140 "perf2.sj"
                    sjt_functionParam393 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent136, sjt_functionParam393, &sjt_capture110);
#line 151
                    sjt_functionParam392 = sjt_capture110 * g_scale;
#line 151
                    sjt_functionParam394 = 0.0f;
#line 151
                    sjf_glvertex3f(sjt_functionParam390, sjt_functionParam392, sjt_functionParam394);
#line 7 "lib/common/array.sj"
                    sjt_parent137 = &_parent->datavert4x;
#line 140 "perf2.sj"
                    sjt_functionParam396 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent137, sjt_functionParam396, &sjt_capture111);
#line 152
                    sjt_functionParam395 = sjt_capture111 * g_scale;
#line 7 "lib/common/array.sj"
                    sjt_parent138 = &_parent->datavert4y;
#line 140 "perf2.sj"
                    sjt_functionParam398 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent138, sjt_functionParam398, &sjt_capture112);
#line 152
                    sjt_functionParam397 = sjt_capture112 * g_scale;
#line 152
                    sjt_functionParam399 = 0.0f;
#line 152
                    sjf_glvertex3f(sjt_functionParam395, sjt_functionParam397, sjt_functionParam399);
#line 7 "lib/common/array.sj"
                    sjt_parent139 = &_parent->datavert5x;
#line 140 "perf2.sj"
                    sjt_functionParam401 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent139, sjt_functionParam401, &sjt_capture113);
#line 153
                    sjt_functionParam400 = sjt_capture113 * g_scale;
#line 7 "lib/common/array.sj"
                    sjt_parent140 = &_parent->datavert5y;
#line 140 "perf2.sj"
                    sjt_functionParam403 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent140, sjt_functionParam403, &sjt_capture114);
#line 153
                    sjt_functionParam402 = sjt_capture114 * g_scale;
#line 153
                    sjt_functionParam404 = 0.0f;
#line 153
                    sjf_glvertex3f(sjt_functionParam400, sjt_functionParam402, sjt_functionParam404);
#line 7 "lib/common/array.sj"
                    sjt_parent141 = &_parent->datahotizont1x;
#line 140 "perf2.sj"
                    sjt_functionParam406 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent141, sjt_functionParam406, &sjt_capture115);
#line 155
                    sjt_functionParam405 = ((sjt_capture115 * g_scale) + 4.35f) + (1.0f / 3.0f);
#line 7 "lib/common/array.sj"
                    sjt_parent142 = &_parent->datahotizont1y;
#line 140 "perf2.sj"
                    sjt_functionParam408 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent142, sjt_functionParam408, &sjt_capture116);
#line 155
                    sjt_functionParam407 = (sjt_capture116 * g_scale) + 3.8f;
#line 155
                    sjt_functionParam409 = 0.0f;
#line 155
                    sjf_glvertex3f(sjt_functionParam405, sjt_functionParam407, sjt_functionParam409);
#line 7 "lib/common/array.sj"
                    sjt_parent143 = &_parent->datahotizont2x;
#line 140 "perf2.sj"
                    sjt_functionParam411 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent143, sjt_functionParam411, &sjt_capture117);
#line 156
                    sjt_functionParam410 = ((sjt_capture117 * g_scale) + 2.18f) + (1.0f / 3.0f);
#line 7 "lib/common/array.sj"
                    sjt_parent144 = &_parent->datahotizont2y;
#line 140 "perf2.sj"
                    sjt_functionParam413 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent144, sjt_functionParam413, &sjt_capture118);
#line 156
                    sjt_functionParam412 = (sjt_capture118 * g_scale) + 1.8f;
#line 156
                    sjt_functionParam414 = 0.0f;
#line 156
                    sjf_glvertex3f(sjt_functionParam410, sjt_functionParam412, sjt_functionParam414);
#line 7 "lib/common/array.sj"
                    sjt_parent145 = &_parent->datahotizont3x;
#line 140 "perf2.sj"
                    sjt_functionParam416 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent145, sjt_functionParam416, &sjt_capture119);
#line 157
                    sjt_functionParam415 = ((sjt_capture119 * g_scale) + 2.34f) + (1.0f / 3.0f);
#line 7 "lib/common/array.sj"
                    sjt_parent146 = &_parent->datahotizont3y;
#line 140 "perf2.sj"
                    sjt_functionParam418 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent146, sjt_functionParam418, &sjt_capture120);
#line 157
                    sjt_functionParam417 = (sjt_capture120 * g_scale) + 0.8f;
#line 157
                    sjt_functionParam419 = 0.0f;
#line 157
                    sjf_glvertex3f(sjt_functionParam415, sjt_functionParam417, sjt_functionParam419);
#line 7 "lib/common/array.sj"
                    sjt_parent147 = &_parent->datahotizont4x;
#line 140 "perf2.sj"
                    sjt_functionParam421 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent147, sjt_functionParam421, &sjt_capture121);
#line 158
                    sjt_functionParam420 = ((sjt_capture121 * g_scale) + 1.65f) + (1.0f / 3.0f);
#line 7 "lib/common/array.sj"
                    sjt_parent148 = &_parent->datahotizont4y;
#line 140 "perf2.sj"
                    sjt_functionParam423 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent148, sjt_functionParam423, &sjt_capture122);
#line 158
                    sjt_functionParam422 = (sjt_capture122 * g_scale) - 1.2f;
#line 158
                    sjt_functionParam424 = 0.0f;
#line 158
                    sjf_glvertex3f(sjt_functionParam420, sjt_functionParam422, sjt_functionParam424);
#line 7 "lib/common/array.sj"
                    sjt_parent149 = &_parent->datahotizont5x;
#line 140 "perf2.sj"
                    sjt_functionParam426 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent149, sjt_functionParam426, &sjt_capture123);
#line 159
                    sjt_functionParam425 = ((sjt_capture123 * g_scale) + 1.35f) + (1.0f / 3.0f);
#line 7 "lib/common/array.sj"
                    sjt_parent150 = &_parent->datahotizont5y;
#line 140 "perf2.sj"
                    sjt_functionParam428 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent150, sjt_functionParam428, &sjt_capture124);
#line 159
                    sjt_functionParam427 = (sjt_capture124 * g_scale) - 2.2f;
#line 159
                    sjt_functionParam429 = 0.0f;
#line 159
                    sjf_glvertex3f(sjt_functionParam425, sjt_functionParam427, sjt_functionParam429);
#line 7 "lib/common/array.sj"
                    sjt_parent151 = &_parent->datavert1x;
#line 140 "perf2.sj"
                    sjt_functionParam431 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent151, sjt_functionParam431, &sjt_capture125);
#line 161
                    sjt_functionParam430 = ((sjt_capture125 * g_scale) + 4.005f) + (1.0f / 6.0f);
#line 7 "lib/common/array.sj"
                    sjt_parent152 = &_parent->datavert1y;
#line 140 "perf2.sj"
                    sjt_functionParam433 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent152, sjt_functionParam433, &sjt_capture126);
#line 161
                    sjt_functionParam432 = (sjt_capture126 * g_scale) + 0.8f;
#line 161
                    sjt_functionParam434 = 0.0f;
#line 161
                    sjf_glvertex3f(sjt_functionParam430, sjt_functionParam432, sjt_functionParam434);
#line 7 "lib/common/array.sj"
                    sjt_parent153 = &_parent->datavert2x;
#line 140 "perf2.sj"
                    sjt_functionParam436 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent153, sjt_functionParam436, &sjt_capture127);
#line 162
                    sjt_functionParam435 = ((sjt_capture127 * g_scale) + 4.05f) - (1.0f / 6.0f);
#line 7 "lib/common/array.sj"
                    sjt_parent154 = &_parent->datavert2y;
#line 140 "perf2.sj"
                    sjt_functionParam438 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent154, sjt_functionParam438, &sjt_capture128);
#line 162
                    sjt_functionParam437 = (sjt_capture128 * g_scale) + 2.8f;
#line 162
                    sjt_functionParam439 = 0.0f;
#line 162
                    sjf_glvertex3f(sjt_functionParam435, sjt_functionParam437, sjt_functionParam439);
#line 7 "lib/common/array.sj"
                    sjt_parent155 = &_parent->datavert3x;
#line 140 "perf2.sj"
                    sjt_functionParam441 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent155, sjt_functionParam441, &sjt_capture129);
#line 163
                    sjt_functionParam440 = ((sjt_capture129 * g_scale) + 3.0f) - (1.0f / 6.0f);
#line 7 "lib/common/array.sj"
                    sjt_parent156 = &_parent->datavert3y;
#line 140 "perf2.sj"
                    sjt_functionParam443 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent156, sjt_functionParam443, &sjt_capture130);
#line 163
                    sjt_functionParam442 = (sjt_capture130 * g_scale) - 0.2f;
#line 163
                    sjt_functionParam444 = 0.0f;
#line 163
                    sjf_glvertex3f(sjt_functionParam440, sjt_functionParam442, sjt_functionParam444);
#line 7 "lib/common/array.sj"
                    sjt_parent157 = &_parent->datavert4x;
#line 140 "perf2.sj"
                    sjt_functionParam446 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent157, sjt_functionParam446, &sjt_capture131);
#line 164
                    sjt_functionParam445 = ((sjt_capture131 * g_scale) + 2.0f) - (1.0f / 6.0f);
#line 7 "lib/common/array.sj"
                    sjt_parent158 = &_parent->datavert4y;
#line 140 "perf2.sj"
                    sjt_functionParam448 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent158, sjt_functionParam448, &sjt_capture132);
#line 164
                    sjt_functionParam447 = (sjt_capture132 * g_scale) - 0.2f;
#line 164
                    sjt_functionParam449 = 0.0f;
#line 164
                    sjf_glvertex3f(sjt_functionParam445, sjt_functionParam447, sjt_functionParam449);
#line 7 "lib/common/array.sj"
                    sjt_parent159 = &_parent->datavert5x;
#line 140 "perf2.sj"
                    sjt_functionParam451 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent159, sjt_functionParam451, &sjt_capture133);
#line 165
                    sjt_functionParam450 = ((sjt_capture133 * g_scale) + 1.0f) - (1.0f / 6.0f);
#line 7 "lib/common/array.sj"
                    sjt_parent160 = &_parent->datavert5y;
#line 140 "perf2.sj"
                    sjt_functionParam453 = n;
#line 140
                    sjf_array_f32_getat(sjt_parent160, sjt_functionParam453, &sjt_capture134);
#line 165
                    sjt_functionParam452 = (sjt_capture134 * g_scale) - 0.2f;
#line 165
                    sjt_functionParam454 = 0.0f;
#line 165
                    sjf_glvertex3f(sjt_functionParam450, sjt_functionParam452, sjt_functionParam454);
                }
            } else {
                float sjt_capture135;
                float sjt_capture136;
                float sjt_functionParam455;
                int32_t sjt_functionParam456;
                float sjt_functionParam457;
                int32_t sjt_functionParam458;
                float sjt_functionParam459;
                sjs_array_f32* sjt_parent161 = 0;
                sjs_array_f32* sjt_parent162 = 0;

#line 7 "lib/common/array.sj"
                sjt_parent161 = &_parent->datax;
#line 140 "perf2.sj"
                sjt_functionParam456 = n;
#line 140
                sjf_array_f32_getat(sjt_parent161, sjt_functionParam456, &sjt_capture135);
#line 168
                sjt_functionParam455 = sjt_capture135 * g_scale;
#line 7 "lib/common/array.sj"
                sjt_parent162 = &_parent->datay;
#line 140 "perf2.sj"
                sjt_functionParam458 = n;
#line 140
                sjf_array_f32_getat(sjt_parent162, sjt_functionParam458, &sjt_capture136);
#line 168
                sjt_functionParam457 = sjt_capture136 * g_scale;
#line 168
                sjt_functionParam459 = 0.0f;
#line 168
                sjf_glvertex3f(sjt_functionParam455, sjt_functionParam457, sjt_functionParam459);
            }

#line 140 "perf2.sj"
            n++;
        }

#line 140
        sjf_glend();
#line 173
        r = r + g_rotateradius;
#line 131
        sjt_while1 = r < 360.0f;
    }
}

void sjf_test_setrect(sjs_test* _parent, sjs_rect* rect_) {
    bool result3;
    bool sjt_capture6;
    sjs_rect* sjt_functionParam28 = 0;
    sjs_rect* sjt_parent12 = 0;

#line 15 "lib/ui/rect.sj"
    sjt_parent12 = &_parent->_rect;
#line 89 "perf2.sj"
    sjt_functionParam28 = rect_;
#line 89
    sjf_rect_isequal(sjt_parent12, sjt_functionParam28, &sjt_capture6);
#line 90
    result3 = !sjt_capture6;
    if (result3) {
        if (_parent->_rect._refCount == 1) { sjf_rect_destroy(&_parent->_rect); }
;
#line 89 "perf2.sj"
        sjf_rect_copy(&_parent->_rect, rect_);
#line 94
        glEnable(GL_LIGHTING);
#line 95
        // glLightModelfv(GL_LIGHT_MODEL_AMBIENT, &a_light.x);
#line 96
        // glLightfv(GL_LIGHT0, GL_DIFFUSE, &s_light.x);
#line 97
        // glLightfv(GL_LIGHT0, GL_POSITION, &l_pos.x);
#line 98
        glEnable(GL_LIGHT0);
#line 100
        glEnable(GL_COLOR_MATERIAL);
#line 101
        //glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
#line 104
        glEnable(GL_BLEND);
#line 105
        glEnable(GL_CULL_FACE);    
#line 106
        glBlendFunc(GL_ONE, GL_ONE);
#line 109
        glMatrixMode(GL_PROJECTION);
#line 110
        glLoadIdentity();        
#line 112
        gluPerspective(g_persp, (GLfloat) 1920 / (GLfloat) 1080, 0.1f, 100.0f);
#line 113
        glMatrixMode(GL_MODELVIEW);
    }
}

void sjf_type_hash(int32_t val, uint32_t* _return) {
    int32_t sjt_cast1;

#line 5 "lib/common/type.sj"
    sjt_cast1 = val;
#line 6
    (*_return) = (uint32_t)sjt_cast1;
}

void sjf_type_isequal(int32_t l, int32_t r, bool* _return) {
#line 10 "lib/common/type.sj"
    (*_return) = l == r;
}

void sjf_vec3(sjs_vec3* _this) {
}

void sjf_vec3_copy(sjs_vec3* _this, sjs_vec3* _from) {
#line 1 "lib/ui/vec3.sj"
    _this->x = _from->x;
#line 1
    _this->y = _from->y;
#line 1
    _this->z = _from->z;
}

void sjf_vec3_destroy(sjs_vec3* _this) {
}

void sjf_vec3_heap(sjs_vec3* _this) {
}

void sjf_vec4(sjs_vec4* _this) {
}

void sjf_vec4_copy(sjs_vec4* _this, sjs_vec4* _from) {
#line 1 "lib/ui/vec4.sj"
    _this->x = _from->x;
#line 1
    _this->y = _from->y;
#line 1
    _this->z = _from->z;
#line 1
    _this->w = _from->w;
}

void sjf_vec4_destroy(sjs_vec4* _this) {
}

void sjf_vec4_heap(sjs_vec4* _this) {
}

void sjf_windowrender_disablevsync(void) {
#line 89 "lib/ui/windowRenderer.sj"
    SDL_GL_SetSwapInterval(0);
}

void sjf_windowrenderer(sjs_windowrenderer* _this) {
    sjs_color sjt_call1 = { -1 };
    sjs_color* sjt_functionParam1 = 0;
    int32_t sjt_functionParam2;
    int32_t sjt_functionParam3;
    int32_t sjt_functionParam4;

#line 30 "lib/ui/windowRenderer.sj"
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
#line 31
        halt("SDL_Init Error: %s\n", SDL_GetError());
#line 32
    }
#line 34
    #ifdef __APPLE__
#line 35
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
#line 36
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#line 37
    #else
#line 38
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#line 39
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
#line 40
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#line 41
    #endif
#line 42
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
#line 43
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
#line 45
    _this->win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
#line 46
    if (_this->win == 0) {
#line 47
        halt("SDL_CreateWindow Error: %s\n", SDL_GetError());
#line 48
    }
#line 50
    SDL_GL_CreateContext((SDL_Window*)_this->win);
#line 51
    #ifdef WIN32
#line 52
    GLint GlewInitResult = glewInit();
#line 53
    if (GLEW_OK != GlewInitResult) 
#line 54
    {
#line 55
        halt("ERROR: %s\n", glewGetErrorString(GlewInitResult));
#line 56
    }
#line 57
    #endif
#line 59
    _this->ren = SDL_CreateRenderer((SDL_Window*)_this->win, -1, SDL_RENDERER_ACCELERATED);
#line 60
    if (_this->ren == 0) {
#line 61
        halt("SDL_CreateRenderer Error: %s\n", SDL_GetError());
#line 62
    }
#line 62
    sjt_call1._refCount = 1;
#line 65
    sjt_call1.r = 0.0f;
#line 65
    sjt_call1.g = 0.0f;
#line 65
    sjt_call1.b = 0.0f;
#line 65
    sjt_call1.a = 0.0f;
#line 65
    sjf_color(&sjt_call1);
#line 65
    sjt_functionParam1 = &sjt_call1;
#line 65
    sjf_glclearcolor(sjt_functionParam1);
#line 66
    sjt_functionParam2 = g_glblendfunctype_gl_src_alpha;
#line 66
    sjt_functionParam3 = g_glblendfunctype_gl_one_minus_src_alpha;
#line 66
    sjf_glblendfunc(sjt_functionParam2, sjt_functionParam3);
#line 67
    sjt_functionParam4 = g_glfeature_gl_blend;
#line 67
    sjf_glenable(sjt_functionParam4);

    if (sjt_call1._refCount == 1) { sjf_color_destroy(&sjt_call1); }
;
}

void sjf_windowrenderer_copy(sjs_windowrenderer* _this, sjs_windowrenderer* _from) {
#line 71 "lib/ui/windowRenderer.sj"
    _this->ren = _from->ren;
#line 72
    ptr_retain(_this->ren);
#line 73
    _this->win = _from->win;
#line 74
    ptr_retain(_this->win);
}

void sjf_windowrenderer_destroy(sjs_windowrenderer* _this) {
#line 78 "lib/ui/windowRenderer.sj"
    if (ptr_release(_this->ren)) {
#line 79
        SDL_DestroyRenderer(_this->ren);
#line 80
    }
#line 81
    if (ptr_release(_this->win)) {
#line 82
        SDL_DestroyWindow(_this->win);
#line 83
    }
}

void sjf_windowrenderer_getsize(sjs_windowrenderer* _parent, sjs_size* _return) {
    int32_t h;
    int32_t w;

#line 8 "lib/ui/windowRenderer.sj"
    w = 0;
#line 9
    h = 0;
#line 11
    SDL_GetRendererOutputSize(_parent->ren, &w, &h);
#line 11
    _return->_refCount = 1;
#line 13
    _return->w = w;
#line 13
    _return->h = h;
#line 13
    sjf_size(_return);
}

void sjf_windowrenderer_getsize_heap(sjs_windowrenderer* _parent, sjs_size** _return) {
    int32_t h;
    int32_t w;

#line 8 "lib/ui/windowRenderer.sj"
    w = 0;
#line 9
    h = 0;
#line 11
    SDL_GetRendererOutputSize(_parent->ren, &w, &h);
#line 11
    (*_return) = (sjs_size*)malloc(sizeof(sjs_size));
#line 11
    (*_return)->_refCount = 1;
#line 13
    (*_return)->w = w;
#line 13
    (*_return)->h = h;
#line 13
    sjf_size_heap((*_return));
}

void sjf_windowrenderer_heap(sjs_windowrenderer* _this) {
    sjs_color sjt_call2 = { -1 };
    sjs_color* sjt_functionParam5 = 0;
    int32_t sjt_functionParam6;
    int32_t sjt_functionParam7;
    int32_t sjt_functionParam8;

#line 30 "lib/ui/windowRenderer.sj"
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
#line 31
        halt("SDL_Init Error: %s\n", SDL_GetError());
#line 32
    }
#line 34
    #ifdef __APPLE__
#line 35
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
#line 36
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#line 37
    #else
#line 38
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#line 39
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
#line 40
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#line 41
    #endif
#line 42
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
#line 43
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
#line 45
    _this->win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
#line 46
    if (_this->win == 0) {
#line 47
        halt("SDL_CreateWindow Error: %s\n", SDL_GetError());
#line 48
    }
#line 50
    SDL_GL_CreateContext((SDL_Window*)_this->win);
#line 51
    #ifdef WIN32
#line 52
    GLint GlewInitResult = glewInit();
#line 53
    if (GLEW_OK != GlewInitResult) 
#line 54
    {
#line 55
        halt("ERROR: %s\n", glewGetErrorString(GlewInitResult));
#line 56
    }
#line 57
    #endif
#line 59
    _this->ren = SDL_CreateRenderer((SDL_Window*)_this->win, -1, SDL_RENDERER_ACCELERATED);
#line 60
    if (_this->ren == 0) {
#line 61
        halt("SDL_CreateRenderer Error: %s\n", SDL_GetError());
#line 62
    }
#line 62
    sjt_call2._refCount = 1;
#line 65
    sjt_call2.r = 0.0f;
#line 65
    sjt_call2.g = 0.0f;
#line 65
    sjt_call2.b = 0.0f;
#line 65
    sjt_call2.a = 0.0f;
#line 65
    sjf_color(&sjt_call2);
#line 65
    sjt_functionParam5 = &sjt_call2;
#line 65
    sjf_glclearcolor(sjt_functionParam5);
#line 66
    sjt_functionParam6 = g_glblendfunctype_gl_src_alpha;
#line 66
    sjt_functionParam7 = g_glblendfunctype_gl_one_minus_src_alpha;
#line 66
    sjf_glblendfunc(sjt_functionParam6, sjt_functionParam7);
#line 67
    sjt_functionParam8 = g_glfeature_gl_blend;
#line 67
    sjf_glenable(sjt_functionParam8);

    if (sjt_call2._refCount == 1) { sjf_color_destroy(&sjt_call2); }
;
}

void sjf_windowrenderer_present(sjs_windowrenderer* _parent) {
#line 24 "lib/ui/windowRenderer.sj"
    SDL_GL_SwapWindow((SDL_Window*)_parent->win);
}

void sjf_windowrenderer_setsize(sjs_windowrenderer* _parent, sjs_size* s) {
#line 18 "lib/ui/windowRenderer.sj"
    SDL_SetWindowSize(_parent->win, s->w, s->h);
}

int main(int argc, char** argv) {
    sjs_test_element_vtbl.destroy = (void(*)(void*))sjf_test_destroy;
    sjs_test_element_vtbl.asinterface = (void(*)(sjs_object*,int,sjs_interface*))sjf_test_asinterface;
    sjs_test_element_vtbl.getclasstype = (void(*)(sjs_object*,int*))sjf_test_getclasstype;
    sjs_test_element_vtbl.getsize = (void(*)(sjs_object*,sjs_size*, sjs_size*))sjf_test_getsize;
    sjs_test_element_vtbl.getsize_heap = (void(*)(sjs_object*,sjs_size*, sjs_size**))sjf_test_getsize_heap;
    sjs_test_element_vtbl.getrect = (void(*)(sjs_object*, sjs_rect*))sjf_test_getrect;
    sjs_test_element_vtbl.getrect_heap = (void(*)(sjs_object*, sjs_rect**))sjf_test_getrect_heap;
    sjs_test_element_vtbl.setrect = (void(*)(sjs_object*,sjs_rect*))sjf_test_setrect;
    sjs_test_element_vtbl.render = (void(*)(sjs_object*,sjs_scene2d*))sjf_test_render;
    sjs_test_element_vtbl.firemouseevent = (void(*)(sjs_object*,sjs_mouseevent*, bool*))sjf_test_firemouseevent;
#line 1 "lib/common/log.sj"
    g_loglevel_trace = 0;
#line 1
    g_loglevel_debug = 1;
#line 1
    g_loglevel_info = 2;
#line 1
    g_loglevel_warn = 3;
#line 1
    g_loglevel_error = 4;
#line 1
    g_loglevel_fatal = 5;
#line 1 "lib/ui/borderLayout.sj"
    g_borderposition_fill = 0;
#line 1
    g_borderposition_left = 1;
#line 1
    g_borderposition_right = 2;
#line 1
    g_borderposition_top = 3;
#line 1
    g_borderposition_bottom = 4;
#line 1 "lib/ui/clickGesture.sj"
    g_clickstate_none = 0;
#line 1
    g_clickstate_entered = 1;
#line 1
    g_clickstate_pressed = 2;
#line 1 "lib/ui/flowLayout.sj"
    g_flowlayoutorientation_topbottom = 0;
#line 1
    g_flowlayoutorientation_leftright = 1;
#line 1
    g_flowlayoutorientation_bottomtop = 2;
#line 1
    g_flowlayoutorientation_rightleft = 3;
#line 1 "lib/ui/gl.sj"
    g_glfeature_gl_blend = 0x0BE2;
#line 1
    g_glfeature_gl_cull_face = 0x0B44;
#line 1
    g_glfeature_gl_depth_test = 0x0B71;
#line 1
    g_glfeature_gl_dither = 0x0BD0;
#line 1
    g_glfeature_gl_polygon_offset_fill = 0x8037;
#line 1
    g_glfeature_gl_sample_alpha_to_coverage = 0x809E;
#line 1
    g_glfeature_gl_sample_coverage = 0x80A0;
#line 1
    g_glfeature_gl_scissor_test = 0x0C11;
#line 1
    g_glfeature_gl_stencil_test = 0x0B90;
#line 13
    g_gltexture_gl_texture_2d = 0x0DE1;
#line 13
    g_gltexture_gl_texture_cube_map = 0x8513;
#line 18
    g_gltextureattribute_gl_texture_min_filter = 0x2801;
#line 18
    g_gltextureattribute_gl_texture_mag_filter = 0x2800;
#line 18
    g_gltextureattribute_gl_texture_wrap_s = 0x2802;
#line 18
    g_gltextureattribute_gl_texture_wrap_t = 0x2803;
#line 25
    g_gltexturevalue_gl_clamp_to_edge = 0x812F;
#line 25
    g_gltexturevalue_gl_mirrored_repeat = 0x8370;
#line 25
    g_gltexturevalue_gl_repeat = 0x2901;
#line 25
    g_gltexturevalue_gl_nearest = 0x2600;
#line 25
    g_gltexturevalue_gl_linear = 0x2601;
#line 25
    g_gltexturevalue_gl_nearest_mipmap_nearest = 0x2700;
#line 25
    g_gltexturevalue_gl_linear_mipmap_nearest = 0x2701;
#line 25
    g_gltexturevalue_gl_nearest_mipmap_linear = 0x2702;
#line 25
    g_gltexturevalue_gl_linear_mipmap_linear = 0x2703;
#line 37
    g_gltextureformat_gl_alpha = 0x1906;
#line 37
    g_gltextureformat_gl_luminance = 0x1909;
#line 37
    g_gltextureformat_gl_luminance_alpha = 0x190A;
#line 37
    g_gltextureformat_gl_rgb = 0x1907;
#line 37
    g_gltextureformat_gl_rgba = 0x1908;
#line 45
    g_gltexturetype_gl_unsigned_byte = 0x1401;
#line 45
    g_gltexturetype_gl_unsigned_short_5_6_5 = 0x8363;
#line 45
    g_gltexturetype_gl_unsigned_short_4_4_4_4 = 0x8033;
#line 45
    g_gltexturetype_gl_unsigned_short_5_5_5_1 = 0x8034;
#line 52
    g_glframebufferattachment_gl_color_attachment0 = 0x8CE0;
#line 52
    g_glframebufferattachment_gl_depth_attachment = 0x8D00;
#line 52
    g_glframebufferattachment_gl_stencil_attachment = 0x8D20;
#line 58
    g_glframebuffertexture_gl_texture_2d = 0x0DE1;
#line 58
    g_glframebuffertexture_gl_texture_cube_map_positive_x = 0x8515;
#line 58
    g_glframebuffertexture_gl_texture_cube_map_negative_x = 0x8516;
#line 58
    g_glframebuffertexture_gl_texture_cube_map_positive_y = 0x8517;
#line 58
    g_glframebuffertexture_gl_texture_cube_map_negative_y = 0x8518;
#line 58
    g_glframebuffertexture_gl_texture_cube_map_positive_z = 0x8519;
#line 58
    g_glframebuffertexture_gl_texture_cube_map_negative_z = 0x851A;
#line 68
    g_glrenderbufferformat_gl_rgba4 = 0x8056;
#line 68
    g_glrenderbufferformat_gl_rgb565 = 0x8D62;
#line 68
    g_glrenderbufferformat_gl_rgb5_a1 = 0x8057;
#line 68
    g_glrenderbufferformat_gl_depth_component16 = 0x81A5;
#line 68
    g_glrenderbufferformat_gl_stencil_index8 = 0x8D48;
#line 76
    g_glframebufferstatus_gl_framebuffer_complete = 0x8CD5;
#line 76
    g_glframebufferstatus_gl_framebuffer_incomplete_attachment = 0x8CD6;
#line 76
    g_glframebufferstatus_gl_framebuffer_incomplete_missing_attachment = 0x8CD7;
#line 76
    g_glframebufferstatus_gl_framebuffer_unsupported = 0x8CDD;
#line 83
    g_glblendfunctype_gl_zero = 0;
#line 83
    g_glblendfunctype_gl_one = 1;
#line 83
    g_glblendfunctype_gl_src_color = 0x0300;
#line 83
    g_glblendfunctype_gl_one_minus_src_color = 0x0301;
#line 83
    g_glblendfunctype_gl_dst_color = 0x0306;
#line 83
    g_glblendfunctype_gl_one_minus_dst_color = 0x0307;
#line 83
    g_glblendfunctype_gl_src_alpha = 0x0302;
#line 83
    g_glblendfunctype_gl_one_minus_src_alpha = 0x0303;
#line 83
    g_glblendfunctype_gl_dst_alpha = 0x0304;
#line 83
    g_glblendfunctype_gl_one_minus_dst_alpha = 0x0305;
#line 83
    g_glblendfunctype_gl_constant_color = 0x8001;
#line 83
    g_glblendfunctype_gl_one_minus_constant_color = 0x8002;
#line 83
    g_glblendfunctype_gl_constant_alpha = 0x8003;
#line 83
    g_glblendfunctype_gl_one_minus_constant_alpha = 0x8004;
#line 83
    g_glblendfunctype_gl_src_alpha_saturate = 0x0308;
#line 101
    g_gldrawmode_gl_points = 0x0000;
#line 101
    g_gldrawmode_gl_line_strip = 0x0003;
#line 101
    g_gldrawmode_gl_line_loop = 0x0002;
#line 101
    g_gldrawmode_gl_lines = 0x0001;
#line 101
    g_gldrawmode_gl_triangle_strip = 0x0005;
#line 101
    g_gldrawmode_gl_triangle_fan = 0x0006;
#line 101
    g_gldrawmode_gl_triangles = 0x0004;
#line 36 "lib/ui/gridLayout.sj"
    g_gridunittype_fixed = 0;
#line 36
    g_gridunittype_star = 1;
#line 1 "lib/ui/imageElement.sj"
    g_imagestretch_fill = 0;
#line 1
    g_imagestretch_center = 1;
#line 1
    g_imagestretch_aspectratio = 2;
#line 1 "lib/ui/listLayout.sj"
    g_listlayoutorientation_topbottom = 0;
#line 1
    g_listlayoutorientation_leftright = 1;
#line 1
    g_listlayoutorientation_bottomtop = 2;
#line 1
    g_listlayoutorientation_rightleft = 3;
#line 32 "lib/ui/mouse.sj"
    g_mouseeventtype_move = 0;
#line 32
    g_mouseeventtype_up = 1;
#line 32
    g_mouseeventtype_down = 2;
#line 1 "lib/ui/textElement.sj"
    g_texthorizontal_left = 0;
#line 1
    g_texthorizontal_right = 1;
#line 1
    g_texthorizontal_center = 2;
#line 7
    g_textvertical_top = 0;
#line 7
    g_textvertical_bottom = 1;
#line 7
    g_textvertical_center = 2;
#line 1 "lib/common/f32.sj"
    g_f32_pi = 3.14159265358979323846f;
#line 1 "lib/common/i32.sj"
    g_u32_maxvalue = (uint32_t)4294967295u;
#line 3
    result1 = -1;
#line 3
    g_i32_maxvalue = result1 - 2147483647;
#line 4
    g_i32_minvalue = 2147483647;
#line 10 "lib/common/log.sj"
    g_log_includeall._refCount = -1;
#line 10
    sjt_value1._refCount = 1;
#line 10
    sjf_hash_type_bool(&sjt_value1);
#line 11
    sjs_hash_type_bool* copyoption1 = &sjt_value1;
    if (copyoption1 != 0) {
        g_log_excludeall._refCount = 1;
#line 11 "lib/common/log.sj"
        sjf_hash_type_bool_copy(&g_log_excludeall, copyoption1);
    } else {
        g_log_excludeall._refCount = -1;
    }

#line 11
    g_log._refCount = 1;
#line 13
    g_log.minlevel = g_loglevel_warn;
#line 13
    sjs_hash_type_bool* copyoption8 = (g_log_includeall._refCount != -1 ? &g_log_includeall : 0);
    if (copyoption8 != 0) {
        g_log.traceincludes._refCount = 1;
#line 13 "lib/common/log.sj"
        sjf_hash_type_bool_copy(&g_log.traceincludes, copyoption8);
    } else {
        g_log.traceincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption9 = (g_log_includeall._refCount != -1 ? &g_log_includeall : 0);
    if (copyoption9 != 0) {
        g_log.debugincludes._refCount = 1;
#line 13 "lib/common/log.sj"
        sjf_hash_type_bool_copy(&g_log.debugincludes, copyoption9);
    } else {
        g_log.debugincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption10 = (g_log_includeall._refCount != -1 ? &g_log_includeall : 0);
    if (copyoption10 != 0) {
        g_log.infoincludes._refCount = 1;
#line 13 "lib/common/log.sj"
        sjf_hash_type_bool_copy(&g_log.infoincludes, copyoption10);
    } else {
        g_log.infoincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption11 = (g_log_includeall._refCount != -1 ? &g_log_includeall : 0);
    if (copyoption11 != 0) {
        g_log.warnincludes._refCount = 1;
#line 13 "lib/common/log.sj"
        sjf_hash_type_bool_copy(&g_log.warnincludes, copyoption11);
    } else {
        g_log.warnincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption12 = (g_log_includeall._refCount != -1 ? &g_log_includeall : 0);
    if (copyoption12 != 0) {
        g_log.errorincludes._refCount = 1;
#line 13 "lib/common/log.sj"
        sjf_hash_type_bool_copy(&g_log.errorincludes, copyoption12);
    } else {
        g_log.errorincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption13 = (g_log_includeall._refCount != -1 ? &g_log_includeall : 0);
    if (copyoption13 != 0) {
        g_log.fatalincludes._refCount = 1;
#line 13 "lib/common/log.sj"
        sjf_hash_type_bool_copy(&g_log.fatalincludes, copyoption13);
    } else {
        g_log.fatalincludes._refCount = -1;
    }

#line 13
    sjf_log(&g_log);
#line 1 "lib/common/string.sj"
    g_emptystringdata = 0;
#line 3
    g_emptystringdata = "";
#line 2 "lib/common/weakptr.sj"
    ptr_init();
#line 3
    weakptr_init();
#line 7 "lib/common/clock.sj"
    g_clocks_per_sec = 0;
#line 9
    g_clocks_per_sec = CLOCKS_PER_SEC;
#line 9
    g_rootwindowrenderer._refCount = 1;
#line 9
    sjf_windowrenderer(&g_rootwindowrenderer);
#line 9
    g_rootscene._refCount = 1;
#line 9
    g_rootscene._size._refCount = 1;
#line 2 "lib/ui/size.sj"
    g_rootscene._size.w = 0;
#line 3
    g_rootscene._size.h = 0;
#line 3
    sjf_size(&g_rootscene._size);
#line 3
    g_rootscene.model._refCount = 1;
#line 2 "lib/ui/mat4.sj"
    g_rootscene.model.m00 = 0.0f;
#line 3
    g_rootscene.model.m01 = 0.0f;
#line 4
    g_rootscene.model.m02 = 0.0f;
#line 5
    g_rootscene.model.m03 = 0.0f;
#line 6
    g_rootscene.model.m10 = 0.0f;
#line 7
    g_rootscene.model.m11 = 0.0f;
#line 8
    g_rootscene.model.m12 = 0.0f;
#line 9
    g_rootscene.model.m13 = 0.0f;
#line 10
    g_rootscene.model.m20 = 0.0f;
#line 11
    g_rootscene.model.m21 = 0.0f;
#line 12
    g_rootscene.model.m22 = 0.0f;
#line 13
    g_rootscene.model.m23 = 0.0f;
#line 14
    g_rootscene.model.m30 = 0.0f;
#line 15
    g_rootscene.model.m31 = 0.0f;
#line 16
    g_rootscene.model.m32 = 0.0f;
#line 17
    g_rootscene.model.m33 = 0.0f;
#line 17
    sjf_mat4(&g_rootscene.model);
#line 17
    g_rootscene.view._refCount = 1;
#line 2
    g_rootscene.view.m00 = 0.0f;
#line 3
    g_rootscene.view.m01 = 0.0f;
#line 4
    g_rootscene.view.m02 = 0.0f;
#line 5
    g_rootscene.view.m03 = 0.0f;
#line 6
    g_rootscene.view.m10 = 0.0f;
#line 7
    g_rootscene.view.m11 = 0.0f;
#line 8
    g_rootscene.view.m12 = 0.0f;
#line 9
    g_rootscene.view.m13 = 0.0f;
#line 10
    g_rootscene.view.m20 = 0.0f;
#line 11
    g_rootscene.view.m21 = 0.0f;
#line 12
    g_rootscene.view.m22 = 0.0f;
#line 13
    g_rootscene.view.m23 = 0.0f;
#line 14
    g_rootscene.view.m30 = 0.0f;
#line 15
    g_rootscene.view.m31 = 0.0f;
#line 16
    g_rootscene.view.m32 = 0.0f;
#line 17
    g_rootscene.view.m33 = 0.0f;
#line 17
    sjf_mat4(&g_rootscene.view);
#line 17
    g_rootscene.projection._refCount = 1;
#line 2
    g_rootscene.projection.m00 = 0.0f;
#line 3
    g_rootscene.projection.m01 = 0.0f;
#line 4
    g_rootscene.projection.m02 = 0.0f;
#line 5
    g_rootscene.projection.m03 = 0.0f;
#line 6
    g_rootscene.projection.m10 = 0.0f;
#line 7
    g_rootscene.projection.m11 = 0.0f;
#line 8
    g_rootscene.projection.m12 = 0.0f;
#line 9
    g_rootscene.projection.m13 = 0.0f;
#line 10
    g_rootscene.projection.m20 = 0.0f;
#line 11
    g_rootscene.projection.m21 = 0.0f;
#line 12
    g_rootscene.projection.m22 = 0.0f;
#line 13
    g_rootscene.projection.m23 = 0.0f;
#line 14
    g_rootscene.projection.m30 = 0.0f;
#line 15
    g_rootscene.projection.m31 = 0.0f;
#line 16
    g_rootscene.projection.m32 = 0.0f;
#line 17
    g_rootscene.projection.m33 = 0.0f;
#line 17
    sjf_mat4(&g_rootscene.projection);
#line 17
    g_rootscene.windowrect._refCount = 1;
#line 2 "lib/ui/rect.sj"
    g_rootscene.windowrect.x = 0;
#line 3
    g_rootscene.windowrect.y = 0;
#line 4
    g_rootscene.windowrect.w = 0;
#line 5
    g_rootscene.windowrect.h = 0;
#line 5
    sjf_rect(&g_rootscene.windowrect);
#line 5
    sjf_scene2d(&g_rootscene);
#line 5
    g_modelsbyid._refCount = 1;
#line 5
    sjf_hash_string_weak_iface_model(&g_modelsbyid);
#line 5
    g_elementsbyid._refCount = 1;
#line 5
    sjf_hash_string_weak_iface_element(&g_elementsbyid);
#line 5
    g_animator._refCount = 1;
#line 5
    g_animator.animations._refCount = 1;
#line 5
    g_animator.animations.array._refCount = 1;
#line 2 "lib/common/list.sj"
    g_animator.animations.array.datasize = 0;
#line 3 "lib/common/array.sj"
    g_animator.animations.array.data = 0;
#line 4
    g_animator.animations.array.isglobal = false;
#line 5
    g_animator.animations.array.count = 0;
#line 5
    sjf_array_heap_iface_animation(&g_animator.animations.array);
#line 5
    sjf_list_heap_iface_animation(&g_animator.animations);
#line 29 "lib/ui/animation.sj"
    g_animator.current = 0;
#line 29
    sjf_animator(&g_animator);
#line 29
    g_blurhorizontalshader._refCount = 1;
#line 29
    g_blurhorizontalshader.vertex._refCount = 1;
#line 1 "lib/ui/blurEffect.sj"
    g_blurhorizontalshader.vertex.count = 20;
#line 1
    g_blurhorizontalshader.vertex.data._refCount = 1;
#line 1
    g_blurhorizontalshader.vertex.data.datasize = 20;
#line 1
    g_blurhorizontalshader.vertex.data.data = (void*)sjg_string1;
#line 1
    g_blurhorizontalshader.vertex.data.isglobal = true;
#line 1
    g_blurhorizontalshader.vertex.data.count = 20;
#line 1
    sjf_array_char(&g_blurhorizontalshader.vertex.data);
#line 14 "lib/common/string.sj"
    g_blurhorizontalshader.vertex._isnullterminated = false;
#line 14
    sjf_string(&g_blurhorizontalshader.vertex);
#line 14
    g_blurhorizontalshader.pixel._refCount = 1;
#line 1 "lib/ui/blurEffect.sj"
    g_blurhorizontalshader.pixel.count = 28;
#line 1
    g_blurhorizontalshader.pixel.data._refCount = 1;
#line 1
    g_blurhorizontalshader.pixel.data.datasize = 28;
#line 1
    g_blurhorizontalshader.pixel.data.data = (void*)sjg_string2;
#line 1
    g_blurhorizontalshader.pixel.data.isglobal = true;
#line 1
    g_blurhorizontalshader.pixel.data.count = 28;
#line 1
    sjf_array_char(&g_blurhorizontalshader.pixel.data);
#line 14 "lib/common/string.sj"
    g_blurhorizontalshader.pixel._isnullterminated = false;
#line 14
    sjf_string(&g_blurhorizontalshader.pixel);
#line 14
    sjf_shader(&g_blurhorizontalshader);
#line 14
    g_blurverticalshader._refCount = 1;
#line 14
    g_blurverticalshader.vertex._refCount = 1;
#line 2 "lib/ui/blurEffect.sj"
    g_blurverticalshader.vertex.count = 20;
#line 2
    g_blurverticalshader.vertex.data._refCount = 1;
#line 2
    g_blurverticalshader.vertex.data.datasize = 20;
#line 2
    g_blurverticalshader.vertex.data.data = (void*)sjg_string1;
#line 2
    g_blurverticalshader.vertex.data.isglobal = true;
#line 2
    g_blurverticalshader.vertex.data.count = 20;
#line 2
    sjf_array_char(&g_blurverticalshader.vertex.data);
#line 14 "lib/common/string.sj"
    g_blurverticalshader.vertex._isnullterminated = false;
#line 14
    sjf_string(&g_blurverticalshader.vertex);
#line 14
    g_blurverticalshader.pixel._refCount = 1;
#line 2 "lib/ui/blurEffect.sj"
    g_blurverticalshader.pixel.count = 26;
#line 2
    g_blurverticalshader.pixel.data._refCount = 1;
#line 2
    g_blurverticalshader.pixel.data.datasize = 26;
#line 2
    g_blurverticalshader.pixel.data.data = (void*)sjg_string3;
#line 2
    g_blurverticalshader.pixel.data.isglobal = true;
#line 2
    g_blurverticalshader.pixel.data.count = 26;
#line 2
    sjf_array_char(&g_blurverticalshader.pixel.data);
#line 14 "lib/common/string.sj"
    g_blurverticalshader.pixel._isnullterminated = false;
#line 14
    sjf_string(&g_blurverticalshader.pixel);
#line 14
    sjf_shader(&g_blurverticalshader);
#line 14
    g_colors_red._refCount = 1;
#line 2 "lib/ui/color.sj"
    g_colors_red.r = 1.0f;
#line 2
    g_colors_red.g = 0.0f;
#line 2
    g_colors_red.b = 0.0f;
#line 14
    g_colors_red.a = 1.0f;
#line 14
    sjf_color(&g_colors_red);
#line 14
    g_colors_green._refCount = 1;
#line 3
    g_colors_green.r = 0.0f;
#line 3
    g_colors_green.g = 1.0f;
#line 3
    g_colors_green.b = 0.0f;
#line 14
    g_colors_green.a = 1.0f;
#line 14
    sjf_color(&g_colors_green);
#line 14
    g_colors_blue._refCount = 1;
#line 4
    g_colors_blue.r = 0.0f;
#line 4
    g_colors_blue.g = 0.0f;
#line 4
    g_colors_blue.b = 1.0f;
#line 14
    g_colors_blue.a = 1.0f;
#line 14
    sjf_color(&g_colors_blue);
#line 14
    g_colors_black._refCount = 1;
#line 5
    g_colors_black.r = 0.0f;
#line 5
    g_colors_black.g = 0.0f;
#line 5
    g_colors_black.b = 0.0f;
#line 14
    g_colors_black.a = 1.0f;
#line 14
    sjf_color(&g_colors_black);
#line 14
    g_colors_white._refCount = 1;
#line 6
    g_colors_white.r = 1.0f;
#line 6
    g_colors_white.g = 1.0f;
#line 6
    g_colors_white.b = 1.0f;
#line 14
    g_colors_white.a = 1.0f;
#line 14
    sjf_color(&g_colors_white);
#line 14
    g_colors_gray._refCount = 1;
#line 7
    g_colors_gray.r = 0.5f;
#line 7
    g_colors_gray.g = 0.5f;
#line 7
    g_colors_gray.b = 0.5f;
#line 14
    g_colors_gray.a = 1.0f;
#line 14
    sjf_color(&g_colors_gray);
#line 14
    g_fadeshader._refCount = 1;
#line 14
    g_fadeshader.vertex._refCount = 1;
#line 1 "lib/ui/fadeEffect.sj"
    g_fadeshader.vertex.count = 20;
#line 1
    g_fadeshader.vertex.data._refCount = 1;
#line 1
    g_fadeshader.vertex.data.datasize = 20;
#line 1
    g_fadeshader.vertex.data.data = (void*)sjg_string1;
#line 1
    g_fadeshader.vertex.data.isglobal = true;
#line 1
    g_fadeshader.vertex.data.count = 20;
#line 1
    sjf_array_char(&g_fadeshader.vertex.data);
#line 14 "lib/common/string.sj"
    g_fadeshader.vertex._isnullterminated = false;
#line 14
    sjf_string(&g_fadeshader.vertex);
#line 14
    g_fadeshader.pixel._refCount = 1;
#line 1 "lib/ui/fadeEffect.sj"
    g_fadeshader.pixel.count = 17;
#line 1
    g_fadeshader.pixel.data._refCount = 1;
#line 1
    g_fadeshader.pixel.data.datasize = 17;
#line 1
    g_fadeshader.pixel.data.data = (void*)sjg_string4;
#line 1
    g_fadeshader.pixel.data.isglobal = true;
#line 1
    g_fadeshader.pixel.data.count = 17;
#line 1
    sjf_array_char(&g_fadeshader.pixel.data);
#line 14 "lib/common/string.sj"
    g_fadeshader.pixel._isnullterminated = false;
#line 14
    sjf_string(&g_fadeshader.pixel);
#line 14
    sjf_shader(&g_fadeshader);
#line 14
    g_fonthash._refCount = 1;
#line 14
    sjf_hash_fontkey_weak_font(&g_fonthash);
#line 14
    g_glviewports._refCount = 1;
#line 14
    g_glviewports.array._refCount = 1;
#line 2 "lib/common/list.sj"
    g_glviewports.array.datasize = 0;
#line 3 "lib/common/array.sj"
    g_glviewports.array.data = 0;
#line 4
    g_glviewports.array.isglobal = false;
#line 5
    g_glviewports.array.count = 0;
#line 5
    sjf_array_rect(&g_glviewports.array);
#line 5
    sjf_list_rect(&g_glviewports);
#line 5
    g_glframebuffers._refCount = 1;
#line 5
    g_glframebuffers.array._refCount = 1;
#line 2 "lib/common/list.sj"
    g_glframebuffers.array.datasize = 0;
#line 3 "lib/common/array.sj"
    g_glframebuffers.array.data = 0;
#line 4
    g_glframebuffers.array.isglobal = false;
#line 5
    g_glframebuffers.array.count = 0;
#line 5
    sjf_array_u32(&g_glframebuffers.array);
#line 5
    sjf_list_u32(&g_glframebuffers);
#line 340 "lib/ui/gl.sj"
    glid_init();
#line 340
    g_looplastrect._refCount = 1;
#line 2 "lib/ui/rect.sj"
    g_looplastrect.x = 0;
#line 3
    g_looplastrect.y = 0;
#line 4
    g_looplastrect.w = 0;
#line 5
    g_looplastrect.h = 0;
#line 5
    sjf_rect(&g_looplastrect);
#line 3 "lib/ui/loop.sj"
    g_mainloop_lasttick = 0;
#line 4
    g_mainloop_frames = 0;
#line 5
    g_mainloop_showfps = false;
#line 6
    g_mainloop_shouldcontinue = true;
#line 1 "lib/ui/mouse.sj"
    g_mouse_captureelement._parent = 0;
#line 1
    g_boxshader._refCount = 1;
#line 1
    g_boxshader.vertex._refCount = 1;
#line 1 "lib/ui/shader.sj"
    g_boxshader.vertex.count = 20;
#line 1
    g_boxshader.vertex.data._refCount = 1;
#line 1
    g_boxshader.vertex.data.datasize = 20;
#line 1
    g_boxshader.vertex.data.data = (void*)sjg_string5;
#line 1
    g_boxshader.vertex.data.isglobal = true;
#line 1
    g_boxshader.vertex.data.count = 20;
#line 1
    sjf_array_char(&g_boxshader.vertex.data);
#line 14 "lib/common/string.sj"
    g_boxshader.vertex._isnullterminated = false;
#line 14
    sjf_string(&g_boxshader.vertex);
#line 14
    g_boxshader.pixel._refCount = 1;
#line 1 "lib/ui/shader.sj"
    g_boxshader.pixel.count = 20;
#line 1
    g_boxshader.pixel.data._refCount = 1;
#line 1
    g_boxshader.pixel.data.datasize = 20;
#line 1
    g_boxshader.pixel.data.data = (void*)sjg_string6;
#line 1
    g_boxshader.pixel.data.isglobal = true;
#line 1
    g_boxshader.pixel.data.count = 20;
#line 1
    sjf_array_char(&g_boxshader.pixel.data);
#line 14 "lib/common/string.sj"
    g_boxshader.pixel._isnullterminated = false;
#line 14
    sjf_string(&g_boxshader.pixel);
#line 14
    sjf_shader(&g_boxshader);
#line 14
    g_imageshader._refCount = 1;
#line 14
    g_imageshader.vertex._refCount = 1;
#line 2 "lib/ui/shader.sj"
    g_imageshader.vertex.count = 20;
#line 2
    g_imageshader.vertex.data._refCount = 1;
#line 2
    g_imageshader.vertex.data.datasize = 20;
#line 2
    g_imageshader.vertex.data.data = (void*)sjg_string1;
#line 2
    g_imageshader.vertex.data.isglobal = true;
#line 2
    g_imageshader.vertex.data.count = 20;
#line 2
    sjf_array_char(&g_imageshader.vertex.data);
#line 14 "lib/common/string.sj"
    g_imageshader.vertex._isnullterminated = false;
#line 14
    sjf_string(&g_imageshader.vertex);
#line 14
    g_imageshader.pixel._refCount = 1;
#line 2 "lib/ui/shader.sj"
    g_imageshader.pixel.count = 20;
#line 2
    g_imageshader.pixel.data._refCount = 1;
#line 2
    g_imageshader.pixel.data.datasize = 20;
#line 2
    g_imageshader.pixel.data.data = (void*)sjg_string7;
#line 2
    g_imageshader.pixel.data.isglobal = true;
#line 2
    g_imageshader.pixel.data.count = 20;
#line 2
    sjf_array_char(&g_imageshader.pixel.data);
#line 14 "lib/common/string.sj"
    g_imageshader.pixel._isnullterminated = false;
#line 14
    sjf_string(&g_imageshader.pixel);
#line 14
    sjf_shader(&g_imageshader);
#line 14
    g_phongcolorshader._refCount = 1;
#line 14
    g_phongcolorshader.vertex._refCount = 1;
#line 3 "lib/ui/shader.sj"
    g_phongcolorshader.vertex.count = 26;
#line 3
    g_phongcolorshader.vertex.data._refCount = 1;
#line 3
    g_phongcolorshader.vertex.data.datasize = 26;
#line 3
    g_phongcolorshader.vertex.data.data = (void*)sjg_string8;
#line 3
    g_phongcolorshader.vertex.data.isglobal = true;
#line 3
    g_phongcolorshader.vertex.data.count = 26;
#line 3
    sjf_array_char(&g_phongcolorshader.vertex.data);
#line 14 "lib/common/string.sj"
    g_phongcolorshader.vertex._isnullterminated = false;
#line 14
    sjf_string(&g_phongcolorshader.vertex);
#line 14
    g_phongcolorshader.pixel._refCount = 1;
#line 3 "lib/ui/shader.sj"
    g_phongcolorshader.pixel.count = 26;
#line 3
    g_phongcolorshader.pixel.data._refCount = 1;
#line 3
    g_phongcolorshader.pixel.data.datasize = 26;
#line 3
    g_phongcolorshader.pixel.data.data = (void*)sjg_string9;
#line 3
    g_phongcolorshader.pixel.data.isglobal = true;
#line 3
    g_phongcolorshader.pixel.data.count = 26;
#line 3
    sjf_array_char(&g_phongcolorshader.pixel.data);
#line 14 "lib/common/string.sj"
    g_phongcolorshader.pixel._isnullterminated = false;
#line 14
    sjf_string(&g_phongcolorshader.pixel);
#line 14
    sjf_shader(&g_phongcolorshader);
#line 14
    g_phongtextureshader._refCount = 1;
#line 14
    g_phongtextureshader.vertex._refCount = 1;
#line 4 "lib/ui/shader.sj"
    g_phongtextureshader.vertex.count = 30;
#line 4
    g_phongtextureshader.vertex.data._refCount = 1;
#line 4
    g_phongtextureshader.vertex.data.datasize = 30;
#line 4
    g_phongtextureshader.vertex.data.data = (void*)sjg_string10;
#line 4
    g_phongtextureshader.vertex.data.isglobal = true;
#line 4
    g_phongtextureshader.vertex.data.count = 30;
#line 4
    sjf_array_char(&g_phongtextureshader.vertex.data);
#line 14 "lib/common/string.sj"
    g_phongtextureshader.vertex._isnullterminated = false;
#line 14
    sjf_string(&g_phongtextureshader.vertex);
#line 14
    g_phongtextureshader.pixel._refCount = 1;
#line 4 "lib/ui/shader.sj"
    g_phongtextureshader.pixel.count = 30;
#line 4
    g_phongtextureshader.pixel.data._refCount = 1;
#line 4
    g_phongtextureshader.pixel.data.datasize = 30;
#line 4
    g_phongtextureshader.pixel.data.data = (void*)sjg_string11;
#line 4
    g_phongtextureshader.pixel.data.isglobal = true;
#line 4
    g_phongtextureshader.pixel.data.count = 30;
#line 4
    sjf_array_char(&g_phongtextureshader.pixel.data);
#line 14 "lib/common/string.sj"
    g_phongtextureshader.pixel._isnullterminated = false;
#line 14
    sjf_string(&g_phongtextureshader.pixel);
#line 14
    sjf_shader(&g_phongtextureshader);
#line 14
    g_textshader._refCount = 1;
#line 14
    g_textshader.vertex._refCount = 1;
#line 5 "lib/ui/shader.sj"
    g_textshader.vertex.count = 24;
#line 5
    g_textshader.vertex.data._refCount = 1;
#line 5
    g_textshader.vertex.data.datasize = 24;
#line 5
    g_textshader.vertex.data.data = (void*)sjg_string12;
#line 5
    g_textshader.vertex.data.isglobal = true;
#line 5
    g_textshader.vertex.data.count = 24;
#line 5
    sjf_array_char(&g_textshader.vertex.data);
#line 14 "lib/common/string.sj"
    g_textshader.vertex._isnullterminated = false;
#line 14
    sjf_string(&g_textshader.vertex);
#line 14
    g_textshader.pixel._refCount = 1;
#line 5 "lib/ui/shader.sj"
    g_textshader.pixel.count = 24;
#line 5
    g_textshader.pixel.data._refCount = 1;
#line 5
    g_textshader.pixel.data.datasize = 24;
#line 5
    g_textshader.pixel.data.data = (void*)sjg_string13;
#line 5
    g_textshader.pixel.data.isglobal = true;
#line 5
    g_textshader.pixel.data.count = 24;
#line 5
    sjf_array_char(&g_textshader.pixel.data);
#line 14 "lib/common/string.sj"
    g_textshader.pixel._isnullterminated = false;
#line 14
    sjf_string(&g_textshader.pixel);
#line 14
    sjf_shader(&g_textshader);
#line 14
    g_style._refCount = 1;
#line 14
    sjf_style(&g_style);
#line 14
    g_vertex_location_texture_normal_format._refCount = 1;
#line 1 "lib/ui/vertexBufferBuilders.sj"
    g_vertex_location_texture_normal_format.count = 32;
#line 1
    g_vertex_location_texture_normal_format.data._refCount = 1;
#line 1
    g_vertex_location_texture_normal_format.data.datasize = 32;
#line 1
    g_vertex_location_texture_normal_format.data.data = (void*)sjg_string14;
#line 1
    g_vertex_location_texture_normal_format.data.isglobal = true;
#line 1
    g_vertex_location_texture_normal_format.data.count = 32;
#line 1
    sjf_array_char(&g_vertex_location_texture_normal_format.data);
#line 14 "lib/common/string.sj"
    g_vertex_location_texture_normal_format._isnullterminated = false;
#line 14
    sjf_string(&g_vertex_location_texture_normal_format);
#line 14
    g_saturateshader._refCount = 1;
#line 14
    g_saturateshader.vertex._refCount = 1;
#line 1 "lib/ui/saturateEffect.sj"
    g_saturateshader.vertex.count = 20;
#line 1
    g_saturateshader.vertex.data._refCount = 1;
#line 1
    g_saturateshader.vertex.data.datasize = 20;
#line 1
    g_saturateshader.vertex.data.data = (void*)sjg_string1;
#line 1
    g_saturateshader.vertex.data.isglobal = true;
#line 1
    g_saturateshader.vertex.data.count = 20;
#line 1
    sjf_array_char(&g_saturateshader.vertex.data);
#line 14 "lib/common/string.sj"
    g_saturateshader.vertex._isnullterminated = false;
#line 14
    sjf_string(&g_saturateshader.vertex);
#line 14
    g_saturateshader.pixel._refCount = 1;
#line 1 "lib/ui/saturateEffect.sj"
    g_saturateshader.pixel.count = 21;
#line 1
    g_saturateshader.pixel.data._refCount = 1;
#line 1
    g_saturateshader.pixel.data.datasize = 21;
#line 1
    g_saturateshader.pixel.data.data = (void*)sjg_string15;
#line 1
    g_saturateshader.pixel.data.isglobal = true;
#line 1
    g_saturateshader.pixel.data.count = 21;
#line 1
    sjf_array_char(&g_saturateshader.pixel.data);
#line 14 "lib/common/string.sj"
    g_saturateshader.pixel._isnullterminated = false;
#line 14
    sjf_string(&g_saturateshader.pixel);
#line 14
    sjf_shader(&g_saturateshader);
#line 14
    g_a_light._refCount = 1;
#line 33 "perf2.sj"
    g_a_light.x = 0.2f;
#line 33
    g_a_light.y = 0.2f;
#line 33
    g_a_light.z = 0.2f;
#line 33
    g_a_light.w = 1.0f;
#line 33
    sjf_vec4(&g_a_light);
#line 33
    g_s_light._refCount = 1;
#line 34
    g_s_light.x = 0.9f;
#line 34
    g_s_light.y = 0.8f;
#line 34
    g_s_light.z = 0.8f;
#line 34
    g_s_light.w = 1.0f;
#line 34
    sjf_vec4(&g_s_light);
#line 34
    g_l_pos._refCount = 1;
#line 35
    result2 = -0.005f;
#line 35
    g_l_pos.x = result2;
#line 35
    g_l_pos.y = 0.0005f;
#line 35
    g_l_pos.z = 0.0f;
#line 35
    g_l_pos.w = 0.0f;
#line 35
    sjf_vec4(&g_l_pos);
#line 36
    g_width = 1920;
#line 37
    g_height = 1080;
#line 38
    g_oncept = 0;
#line 39
    g_dotsscale = 4000;
#line 40
    sjt_cast3 = g_dotsscale;
#line 40
    sjt_cast2 = g_f32_pi * (float)sjt_cast3;
#line 40
    g_dots = (int32_t)sjt_cast2;
#line 41
    g_rotateradius = 1.0f;
#line 42
    g_persp = 45.0f;
#line 42
    g_stateof._refCount = 1;
#line 43
    g_stateof.datasize = 3;
#line 3 "lib/common/array.sj"
    g_stateof.data = 0;
#line 4
    g_stateof.isglobal = false;
#line 5
    g_stateof.count = 0;
#line 5
    sjf_array_bool(&g_stateof);
#line 43 "perf2.sj"
    sjs_array_bool* array1;
#line 43
    array1 = &g_stateof;
#line 43
    sjt_parent4 = array1;
#line 43
    sjt_functionParam12 = 0;
#line 43
    sjt_functionParam13 = true;
#line 43
    sjf_array_bool_initat(sjt_parent4, sjt_functionParam12, sjt_functionParam13);
#line 43
    sjt_parent5 = array1;
#line 43
    sjt_functionParam14 = 1;
#line 43
    sjt_functionParam15 = true;
#line 43
    sjf_array_bool_initat(sjt_parent5, sjt_functionParam14, sjt_functionParam15);
#line 43
    sjt_parent6 = array1;
#line 43
    sjt_functionParam16 = 2;
#line 43
    sjt_functionParam17 = true;
#line 43
    sjf_array_bool_initat(sjt_parent6, sjt_functionParam16, sjt_functionParam17);
#line 43
    g_stateofdir._refCount = 1;
#line 44
    g_stateofdir.datasize = 3;
#line 3 "lib/common/array.sj"
    g_stateofdir.data = 0;
#line 4
    g_stateofdir.isglobal = false;
#line 5
    g_stateofdir.count = 0;
#line 5
    sjf_array_bool(&g_stateofdir);
#line 44 "perf2.sj"
    sjs_array_bool* array2;
#line 44
    array2 = &g_stateofdir;
#line 44
    sjt_parent7 = array2;
#line 44
    sjt_functionParam18 = 0;
#line 44
    sjt_functionParam19 = true;
#line 44
    sjf_array_bool_initat(sjt_parent7, sjt_functionParam18, sjt_functionParam19);
#line 44
    sjt_parent8 = array2;
#line 44
    sjt_functionParam20 = 1;
#line 44
    sjt_functionParam21 = true;
#line 44
    sjf_array_bool_initat(sjt_parent8, sjt_functionParam20, sjt_functionParam21);
#line 44
    sjt_parent9 = array2;
#line 44
    sjt_functionParam22 = 2;
#line 44
    sjt_functionParam23 = true;
#line 44
    sjf_array_bool_initat(sjt_parent9, sjt_functionParam22, sjt_functionParam23);
#line 44
    g_mainrot._refCount = 1;
#line 45
    g_mainrot.datasize = 2;
#line 3 "lib/common/array.sj"
    g_mainrot.data = 0;
#line 4
    g_mainrot.isglobal = false;
#line 5
    g_mainrot.count = 0;
#line 5
    sjf_array_bool(&g_mainrot);
#line 45 "perf2.sj"
    sjs_array_bool* array3;
#line 45
    array3 = &g_mainrot;
#line 45
    sjt_parent10 = array3;
#line 45
    sjt_functionParam24 = 0;
#line 45
    sjt_functionParam25 = false;
#line 45
    sjf_array_bool_initat(sjt_parent10, sjt_functionParam24, sjt_functionParam25);
#line 45
    sjt_parent11 = array3;
#line 45
    sjt_functionParam26 = 1;
#line 45
    sjt_functionParam27 = false;
#line 45
    sjf_array_bool_initat(sjt_parent11, sjt_functionParam26, sjt_functionParam27);
#line 46
    g_scale = 0.5f;
#line 47
    g_img_dotsscale = 100;
#line 48
    sjt_cast5 = g_img_dotsscale;
#line 48
    sjt_cast4 = g_f32_pi * (float)sjt_cast5;
#line 48
    g_img_dots = (int32_t)sjt_cast4;
#line 48
    sjt_call3._refCount = 1;
#line 51
    sjt_call3.funcid = 0;
#line 52
    sjt_call3.lastfuncid = 0;
#line 52
    sjt_call4._refCount = 1;
#line 53
    sjt_call4.datasize = g_dots;
#line 3 "lib/common/array.sj"
    sjt_call4.data = 0;
#line 4
    sjt_call4.isglobal = false;
#line 5
    sjt_call4.count = 0;
#line 5
    sjf_array_f32(&sjt_call4);
#line 53 "perf2.sj"
    sjt_parent163 = &sjt_call4;
#line 53
    sjt_functionParam460 = 0.0f;
#line 53
    sjf_array_f32_init(sjt_parent163, sjt_functionParam460, &sjt_call3.datax);
#line 53
    sjt_call5._refCount = 1;
#line 54
    sjt_call5.datasize = g_dots;
#line 3 "lib/common/array.sj"
    sjt_call5.data = 0;
#line 4
    sjt_call5.isglobal = false;
#line 5
    sjt_call5.count = 0;
#line 5
    sjf_array_f32(&sjt_call5);
#line 54 "perf2.sj"
    sjt_parent164 = &sjt_call5;
#line 54
    sjt_functionParam461 = 0.0f;
#line 54
    sjf_array_f32_init(sjt_parent164, sjt_functionParam461, &sjt_call3.datay);
#line 55
    sjt_call3.rotatex = 0.0f;
#line 56
    sjt_call3.rotatey = 0.0f;
#line 57
    sjt_call3.rotatez = 0.0f;
#line 57
    sjt_call6._refCount = 1;
#line 59
    sjt_call6.datasize = g_img_dots;
#line 3 "lib/common/array.sj"
    sjt_call6.data = 0;
#line 4
    sjt_call6.isglobal = false;
#line 5
    sjt_call6.count = 0;
#line 5
    sjf_array_f32(&sjt_call6);
#line 59 "perf2.sj"
    sjt_parent165 = &sjt_call6;
#line 59
    sjt_functionParam462 = 0.0f;
#line 59
    sjf_array_f32_init(sjt_parent165, sjt_functionParam462, &sjt_call3.datavert1x);
#line 59
    sjt_call7._refCount = 1;
#line 60
    sjt_call7.datasize = g_img_dots;
#line 3 "lib/common/array.sj"
    sjt_call7.data = 0;
#line 4
    sjt_call7.isglobal = false;
#line 5
    sjt_call7.count = 0;
#line 5
    sjf_array_f32(&sjt_call7);
#line 60 "perf2.sj"
    sjt_parent166 = &sjt_call7;
#line 60
    sjt_functionParam463 = 0.0f;
#line 60
    sjf_array_f32_init(sjt_parent166, sjt_functionParam463, &sjt_call3.datavert1y);
#line 60
    sjt_call8._refCount = 1;
#line 61
    sjt_call8.datasize = g_img_dots;
#line 3 "lib/common/array.sj"
    sjt_call8.data = 0;
#line 4
    sjt_call8.isglobal = false;
#line 5
    sjt_call8.count = 0;
#line 5
    sjf_array_f32(&sjt_call8);
#line 61 "perf2.sj"
    sjt_parent167 = &sjt_call8;
#line 61
    sjt_functionParam464 = 0.0f;
#line 61
    sjf_array_f32_init(sjt_parent167, sjt_functionParam464, &sjt_call3.datavert2x);
#line 61
    sjt_call9._refCount = 1;
#line 62
    sjt_call9.datasize = g_img_dots;
#line 3 "lib/common/array.sj"
    sjt_call9.data = 0;
#line 4
    sjt_call9.isglobal = false;
#line 5
    sjt_call9.count = 0;
#line 5
    sjf_array_f32(&sjt_call9);
#line 62 "perf2.sj"
    sjt_parent168 = &sjt_call9;
#line 62
    sjt_functionParam465 = 0.0f;
#line 62
    sjf_array_f32_init(sjt_parent168, sjt_functionParam465, &sjt_call3.datavert2y);
#line 62
    sjt_call10._refCount = 1;
#line 63
    sjt_call10.datasize = g_img_dots;
#line 3 "lib/common/array.sj"
    sjt_call10.data = 0;
#line 4
    sjt_call10.isglobal = false;
#line 5
    sjt_call10.count = 0;
#line 5
    sjf_array_f32(&sjt_call10);
#line 63 "perf2.sj"
    sjt_parent169 = &sjt_call10;
#line 63
    sjt_functionParam466 = 0.0f;
#line 63
    sjf_array_f32_init(sjt_parent169, sjt_functionParam466, &sjt_call3.datavert3x);
#line 63
    sjt_call11._refCount = 1;
#line 64
    sjt_call11.datasize = g_img_dots;
#line 3 "lib/common/array.sj"
    sjt_call11.data = 0;
#line 4
    sjt_call11.isglobal = false;
#line 5
    sjt_call11.count = 0;
#line 5
    sjf_array_f32(&sjt_call11);
#line 64 "perf2.sj"
    sjt_parent170 = &sjt_call11;
#line 64
    sjt_functionParam467 = 0.0f;
#line 64
    sjf_array_f32_init(sjt_parent170, sjt_functionParam467, &sjt_call3.datavert3y);
#line 64
    sjt_call12._refCount = 1;
#line 65
    sjt_call12.datasize = g_img_dots;
#line 3 "lib/common/array.sj"
    sjt_call12.data = 0;
#line 4
    sjt_call12.isglobal = false;
#line 5
    sjt_call12.count = 0;
#line 5
    sjf_array_f32(&sjt_call12);
#line 65 "perf2.sj"
    sjt_parent171 = &sjt_call12;
#line 65
    sjt_functionParam468 = 0.0f;
#line 65
    sjf_array_f32_init(sjt_parent171, sjt_functionParam468, &sjt_call3.datavert4x);
#line 65
    sjt_call13._refCount = 1;
#line 66
    sjt_call13.datasize = g_img_dots;
#line 3 "lib/common/array.sj"
    sjt_call13.data = 0;
#line 4
    sjt_call13.isglobal = false;
#line 5
    sjt_call13.count = 0;
#line 5
    sjf_array_f32(&sjt_call13);
#line 66 "perf2.sj"
    sjt_parent172 = &sjt_call13;
#line 66
    sjt_functionParam469 = 0.0f;
#line 66
    sjf_array_f32_init(sjt_parent172, sjt_functionParam469, &sjt_call3.datavert4y);
#line 66
    sjt_call14._refCount = 1;
#line 67
    sjt_call14.datasize = g_img_dots;
#line 3 "lib/common/array.sj"
    sjt_call14.data = 0;
#line 4
    sjt_call14.isglobal = false;
#line 5
    sjt_call14.count = 0;
#line 5
    sjf_array_f32(&sjt_call14);
#line 67 "perf2.sj"
    sjt_parent173 = &sjt_call14;
#line 67
    sjt_functionParam470 = 0.0f;
#line 67
    sjf_array_f32_init(sjt_parent173, sjt_functionParam470, &sjt_call3.datavert5x);
#line 67
    sjt_call15._refCount = 1;
#line 68
    sjt_call15.datasize = g_img_dots;
#line 3 "lib/common/array.sj"
    sjt_call15.data = 0;
#line 4
    sjt_call15.isglobal = false;
#line 5
    sjt_call15.count = 0;
#line 5
    sjf_array_f32(&sjt_call15);
#line 68 "perf2.sj"
    sjt_parent174 = &sjt_call15;
#line 68
    sjt_functionParam471 = 0.0f;
#line 68
    sjf_array_f32_init(sjt_parent174, sjt_functionParam471, &sjt_call3.datavert5y);
#line 68
    sjt_call16._refCount = 1;
#line 70
    sjt_call16.datasize = g_img_dots;
#line 3 "lib/common/array.sj"
    sjt_call16.data = 0;
#line 4
    sjt_call16.isglobal = false;
#line 5
    sjt_call16.count = 0;
#line 5
    sjf_array_f32(&sjt_call16);
#line 70 "perf2.sj"
    sjt_parent175 = &sjt_call16;
#line 70
    sjt_functionParam472 = 0.0f;
#line 70
    sjf_array_f32_init(sjt_parent175, sjt_functionParam472, &sjt_call3.datahotizont1x);
#line 70
    sjt_call17._refCount = 1;
#line 71
    sjt_call17.datasize = g_img_dots;
#line 3 "lib/common/array.sj"
    sjt_call17.data = 0;
#line 4
    sjt_call17.isglobal = false;
#line 5
    sjt_call17.count = 0;
#line 5
    sjf_array_f32(&sjt_call17);
#line 71 "perf2.sj"
    sjt_parent176 = &sjt_call17;
#line 71
    sjt_functionParam473 = 0.0f;
#line 71
    sjf_array_f32_init(sjt_parent176, sjt_functionParam473, &sjt_call3.datahotizont1y);
#line 71
    sjt_call18._refCount = 1;
#line 72
    sjt_call18.datasize = g_img_dots;
#line 3 "lib/common/array.sj"
    sjt_call18.data = 0;
#line 4
    sjt_call18.isglobal = false;
#line 5
    sjt_call18.count = 0;
#line 5
    sjf_array_f32(&sjt_call18);
#line 72 "perf2.sj"
    sjt_parent177 = &sjt_call18;
#line 72
    sjt_functionParam474 = 0.0f;
#line 72
    sjf_array_f32_init(sjt_parent177, sjt_functionParam474, &sjt_call3.datahotizont2x);
#line 72
    sjt_call19._refCount = 1;
#line 73
    sjt_call19.datasize = g_img_dots;
#line 3 "lib/common/array.sj"
    sjt_call19.data = 0;
#line 4
    sjt_call19.isglobal = false;
#line 5
    sjt_call19.count = 0;
#line 5
    sjf_array_f32(&sjt_call19);
#line 73 "perf2.sj"
    sjt_parent178 = &sjt_call19;
#line 73
    sjt_functionParam475 = 0.0f;
#line 73
    sjf_array_f32_init(sjt_parent178, sjt_functionParam475, &sjt_call3.datahotizont2y);
#line 73
    sjt_call20._refCount = 1;
#line 74
    sjt_call20.datasize = g_img_dots;
#line 3 "lib/common/array.sj"
    sjt_call20.data = 0;
#line 4
    sjt_call20.isglobal = false;
#line 5
    sjt_call20.count = 0;
#line 5
    sjf_array_f32(&sjt_call20);
#line 74 "perf2.sj"
    sjt_parent179 = &sjt_call20;
#line 74
    sjt_functionParam476 = 0.0f;
#line 74
    sjf_array_f32_init(sjt_parent179, sjt_functionParam476, &sjt_call3.datahotizont3x);
#line 74
    sjt_call21._refCount = 1;
#line 75
    sjt_call21.datasize = g_img_dots;
#line 3 "lib/common/array.sj"
    sjt_call21.data = 0;
#line 4
    sjt_call21.isglobal = false;
#line 5
    sjt_call21.count = 0;
#line 5
    sjf_array_f32(&sjt_call21);
#line 75 "perf2.sj"
    sjt_parent180 = &sjt_call21;
#line 75
    sjt_functionParam477 = 0.0f;
#line 75
    sjf_array_f32_init(sjt_parent180, sjt_functionParam477, &sjt_call3.datahotizont3y);
#line 75
    sjt_call22._refCount = 1;
#line 76
    sjt_call22.datasize = g_img_dots;
#line 3 "lib/common/array.sj"
    sjt_call22.data = 0;
#line 4
    sjt_call22.isglobal = false;
#line 5
    sjt_call22.count = 0;
#line 5
    sjf_array_f32(&sjt_call22);
#line 76 "perf2.sj"
    sjt_parent181 = &sjt_call22;
#line 76
    sjt_functionParam478 = 0.0f;
#line 76
    sjf_array_f32_init(sjt_parent181, sjt_functionParam478, &sjt_call3.datahotizont4x);
#line 76
    sjt_call23._refCount = 1;
#line 77
    sjt_call23.datasize = g_img_dots;
#line 3 "lib/common/array.sj"
    sjt_call23.data = 0;
#line 4
    sjt_call23.isglobal = false;
#line 5
    sjt_call23.count = 0;
#line 5
    sjf_array_f32(&sjt_call23);
#line 77 "perf2.sj"
    sjt_parent182 = &sjt_call23;
#line 77
    sjt_functionParam479 = 0.0f;
#line 77
    sjf_array_f32_init(sjt_parent182, sjt_functionParam479, &sjt_call3.datahotizont4y);
#line 77
    sjt_call24._refCount = 1;
#line 78
    sjt_call24.datasize = g_img_dots;
#line 3 "lib/common/array.sj"
    sjt_call24.data = 0;
#line 4
    sjt_call24.isglobal = false;
#line 5
    sjt_call24.count = 0;
#line 5
    sjf_array_f32(&sjt_call24);
#line 78 "perf2.sj"
    sjt_parent183 = &sjt_call24;
#line 78
    sjt_functionParam480 = 0.0f;
#line 78
    sjf_array_f32_init(sjt_parent183, sjt_functionParam480, &sjt_call3.datahotizont5x);
#line 78
    sjt_call25._refCount = 1;
#line 79
    sjt_call25.datasize = g_img_dots;
#line 3 "lib/common/array.sj"
    sjt_call25.data = 0;
#line 4
    sjt_call25.isglobal = false;
#line 5
    sjt_call25.count = 0;
#line 5
    sjf_array_f32(&sjt_call25);
#line 79 "perf2.sj"
    sjt_parent184 = &sjt_call25;
#line 79
    sjt_functionParam481 = 0.0f;
#line 79
    sjf_array_f32_init(sjt_parent184, sjt_functionParam481, &sjt_call3.datahotizont5y);
#line 79
    sjt_call3._rect._refCount = 1;
#line 2 "lib/ui/rect.sj"
    sjt_call3._rect.x = 0;
#line 3
    sjt_call3._rect.y = 0;
#line 4
    sjt_call3._rect.w = 0;
#line 5
    sjt_call3._rect.h = 0;
#line 5
    sjf_rect(&sjt_call3._rect);
#line 5
    sjf_test(&sjt_call3);
#line 454 "perf2.sj"
    sjt_cast6 = &sjt_call3;
#line 1 "lib/ui/element.sj"
    sjf_test_as_sji_element(sjt_cast6, &g_root);
#line 456 "perf2.sj"
    g_mainloop_showfps = true;
#line 456
    sjf_windowrender_disablevsync();
#line 16 "lib/ui/windowRenderer.sj"
    sjt_parent185 = &g_rootwindowrenderer;
#line 16
    sjt_call26._refCount = 1;
#line 458 "perf2.sj"
    sjt_call26.w = 1920;
#line 458
    sjt_call26.h = 1080;
#line 458
    sjf_size(&sjt_call26);
#line 458
    sjt_functionParam482 = &sjt_call26;
#line 458
    sjf_windowrenderer_setsize(sjt_parent185, sjt_functionParam482);
#line 458
    sjf_runloop();
    main_destroy();
    return 0;
}

void main_destroy() {

    if (g_mouse_captureelement._parent != 0) {
        g_mouse_captureelement._parent->_refCount--;
        if (g_mouse_captureelement._parent->_refCount <= 0) {
            g_mouse_captureelement._vtbl->destroy(g_mouse_captureelement._parent);
            free(g_mouse_captureelement._parent);
        }
    }
    if (g_a_light._refCount == 1) { sjf_vec4_destroy(&g_a_light); }
;
    if (g_animator._refCount == 1) { sjf_animator_destroy(&g_animator); }
;
    if (g_blurhorizontalshader._refCount == 1) { sjf_shader_destroy(&g_blurhorizontalshader); }
;
    if (g_blurverticalshader._refCount == 1) { sjf_shader_destroy(&g_blurverticalshader); }
;
    if (g_boxshader._refCount == 1) { sjf_shader_destroy(&g_boxshader); }
;
    if (g_colors_black._refCount == 1) { sjf_color_destroy(&g_colors_black); }
;
    if (g_colors_blue._refCount == 1) { sjf_color_destroy(&g_colors_blue); }
;
    if (g_colors_gray._refCount == 1) { sjf_color_destroy(&g_colors_gray); }
;
    if (g_colors_green._refCount == 1) { sjf_color_destroy(&g_colors_green); }
;
    if (g_colors_red._refCount == 1) { sjf_color_destroy(&g_colors_red); }
;
    if (g_colors_white._refCount == 1) { sjf_color_destroy(&g_colors_white); }
;
    if (g_elementsbyid._refCount == 1) { sjf_hash_string_weak_iface_element_destroy(&g_elementsbyid); }
;
    if (g_fadeshader._refCount == 1) { sjf_shader_destroy(&g_fadeshader); }
;
    if (g_fonthash._refCount == 1) { sjf_hash_fontkey_weak_font_destroy(&g_fonthash); }
;
    if (g_glframebuffers._refCount == 1) { sjf_list_u32_destroy(&g_glframebuffers); }
;
    if (g_glviewports._refCount == 1) { sjf_list_rect_destroy(&g_glviewports); }
;
    if (g_imageshader._refCount == 1) { sjf_shader_destroy(&g_imageshader); }
;
    if (g_l_pos._refCount == 1) { sjf_vec4_destroy(&g_l_pos); }
;
    if (g_log._refCount == 1) { sjf_log_destroy(&g_log); }
;
    if (g_log_excludeall._refCount == 1) { sjf_hash_type_bool_destroy(&g_log_excludeall); }
;
    if (g_log_includeall._refCount == 1) { sjf_hash_type_bool_destroy(&g_log_includeall); }
;
    if (g_looplastrect._refCount == 1) { sjf_rect_destroy(&g_looplastrect); }
;
    if (g_mainrot._refCount == 1) { sjf_array_bool_destroy(&g_mainrot); }
;
    if (g_modelsbyid._refCount == 1) { sjf_hash_string_weak_iface_model_destroy(&g_modelsbyid); }
;
    if (g_phongcolorshader._refCount == 1) { sjf_shader_destroy(&g_phongcolorshader); }
;
    if (g_phongtextureshader._refCount == 1) { sjf_shader_destroy(&g_phongtextureshader); }
;
    if (g_rootscene._refCount == 1) { sjf_scene2d_destroy(&g_rootscene); }
;
    if (g_rootwindowrenderer._refCount == 1) { sjf_windowrenderer_destroy(&g_rootwindowrenderer); }
;
    if (g_s_light._refCount == 1) { sjf_vec4_destroy(&g_s_light); }
;
    if (g_saturateshader._refCount == 1) { sjf_shader_destroy(&g_saturateshader); }
;
    if (g_stateof._refCount == 1) { sjf_array_bool_destroy(&g_stateof); }
;
    if (g_stateofdir._refCount == 1) { sjf_array_bool_destroy(&g_stateofdir); }
;
    if (g_style._refCount == 1) { sjf_style_destroy(&g_style); }
;
    if (g_textshader._refCount == 1) { sjf_shader_destroy(&g_textshader); }
;
    if (g_vertex_location_texture_normal_format._refCount == 1) { sjf_string_destroy(&g_vertex_location_texture_normal_format); }
;
    if (sjt_call10._refCount == 1) { sjf_array_f32_destroy(&sjt_call10); }
;
    if (sjt_call11._refCount == 1) { sjf_array_f32_destroy(&sjt_call11); }
;
    if (sjt_call12._refCount == 1) { sjf_array_f32_destroy(&sjt_call12); }
;
    if (sjt_call13._refCount == 1) { sjf_array_f32_destroy(&sjt_call13); }
;
    if (sjt_call14._refCount == 1) { sjf_array_f32_destroy(&sjt_call14); }
;
    if (sjt_call15._refCount == 1) { sjf_array_f32_destroy(&sjt_call15); }
;
    if (sjt_call16._refCount == 1) { sjf_array_f32_destroy(&sjt_call16); }
;
    if (sjt_call17._refCount == 1) { sjf_array_f32_destroy(&sjt_call17); }
;
    if (sjt_call18._refCount == 1) { sjf_array_f32_destroy(&sjt_call18); }
;
    if (sjt_call19._refCount == 1) { sjf_array_f32_destroy(&sjt_call19); }
;
    if (sjt_call20._refCount == 1) { sjf_array_f32_destroy(&sjt_call20); }
;
    if (sjt_call21._refCount == 1) { sjf_array_f32_destroy(&sjt_call21); }
;
    if (sjt_call22._refCount == 1) { sjf_array_f32_destroy(&sjt_call22); }
;
    if (sjt_call23._refCount == 1) { sjf_array_f32_destroy(&sjt_call23); }
;
    if (sjt_call24._refCount == 1) { sjf_array_f32_destroy(&sjt_call24); }
;
    if (sjt_call25._refCount == 1) { sjf_array_f32_destroy(&sjt_call25); }
;
    if (sjt_call26._refCount == 1) { sjf_size_destroy(&sjt_call26); }
;
    if (sjt_call3._refCount == 1) { sjf_test_destroy(&sjt_call3); }
;
    if (sjt_call4._refCount == 1) { sjf_array_f32_destroy(&sjt_call4); }
;
    if (sjt_call5._refCount == 1) { sjf_array_f32_destroy(&sjt_call5); }
;
    if (sjt_call6._refCount == 1) { sjf_array_f32_destroy(&sjt_call6); }
;
    if (sjt_call7._refCount == 1) { sjf_array_f32_destroy(&sjt_call7); }
;
    if (sjt_call8._refCount == 1) { sjf_array_f32_destroy(&sjt_call8); }
;
    if (sjt_call9._refCount == 1) { sjf_array_f32_destroy(&sjt_call9); }
;
    if (sjt_value1._refCount == 1) { sjf_hash_type_bool_destroy(&sjt_value1); }
;
}