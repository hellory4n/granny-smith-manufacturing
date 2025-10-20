#pragma once

#include <trippin/common.h>
#include <trippin/math.h>

#include "trippin/error.h"

namespace gsm {

// A program on the GPU©®¢™¢™¢™©®©®©®™™™©®©®™™™©®©®™™¢®¢™™
class ShaderProgram;

// Shader. There's different shader classes just in case I decide to add compute
// shaders for some fucking reason.
class Shader
{
protected:
	uint32 _shader = 0;
	friend class ShaderProgram;

	void _check_compilation(const char* shader_type) const;
};

// A vertex shader is a shader that fucks with vertices.
class VertexShader : public Shader
{
public:
	VertexShader(tr::String src);
	void free();
};

// A fragment shader is a shader that fucks with fragments.
class FragmentShader : public Shader
{
public:
	FragmentShader(tr::String src);
	void free();
};

// A program on the GPU©®¢™¢™¢™©®©®©®™™™©®©®™™™©®©®™™¢®¢™™
class ShaderProgram
{
	uint32 _program = 0;

public:
	ShaderProgram();
	void free();

	// Le
	// TODO wtf is le
	void attach(const Shader& shader);
	void link();
	// Uses the program for rendering crap.
	void use();

	// TODO string names are slower
	void set_uniform(tr::String name, bool value);
	void set_uniform(tr::String name, int32 value);
	void set_uniform(tr::String name, uint32 value);
	void set_uniform(tr::String name, float32 value);
	void set_uniform(tr::String name, tr::Vec2<float32> value);
	void set_uniform(tr::String name, tr::Vec3<float32> value);
	void set_uniform(tr::String name, tr::Vec4<float32> value);
	void set_uniform(tr::String name, tr::Vec2<int32> value);
	void set_uniform(tr::String name, tr::Vec3<int32> value);
	void set_uniform(tr::String name, tr::Vec4<int32> value);
	void set_uniform(tr::String name, tr::Vec2<uint32> value);
	void set_uniform(tr::String name, tr::Vec3<uint32> value);
	void set_uniform(tr::String name, tr::Vec4<uint32> value);
	void set_uniform(tr::String name, tr::Matrix4x4 value);
};

// What should happen when texture coordinates go beyond 0-1. See [this
// image](https://learnopengl.com/img/getting-started/texture_wrapping.png) for
// a visual example
enum class TextureWrap
{
	TILE,
	MIRRORED_TILE,
	CLAMP_TO_EDGE,
	CLAMP_TO_BORDER,
};

enum class TextureFilter
{
	NEAREST_NEIGHBOR,
	BILINEAR_FILTER,
};

struct TextureSettings
{
	TextureWrap wrap = TextureWrap::TILE;
	TextureFilter filter = TextureFilter::NEAREST_NEIGHBOR;
	bool mipmaps = true;
};

class Texture
{
	uint32 _id = 0;
	tr::Vec2<uint32> _size = {};

public:
	// Loads a texture duh. Supported formats are .png, .jpeg, .gif (no animation) .bmp, .tga,
	// .psd (composited view only), .hdr (radiance rgbE format), .pic (Softimage pic), and
	// .ppm/.pgm binary
	static tr::Result<Texture> load(tr::String path, TextureSettings settings = {});
	void free();

	// It sets the texture to be the current texture texturing all over the place.
	void use() const;

	// In pixels
	tr::Vec2<uint32> size() const
	{
		return _size;
	}
};

}
