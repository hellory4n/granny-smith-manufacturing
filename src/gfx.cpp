#include "gfx.h"

#include <trippin/iofs.h>

#include <glad/gl.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "state.h"

void gsm::Shader::_check_compilation(const char* shader_type) const
{
	int success;
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);
	if (success == 0) {
		char info_log[512];
		glGetShaderInfoLog(_shader, 512, nullptr, info_log);
		tr::panic("couldn't compile %s shader: %s", shader_type, info_log);
	}
}

gsm::VertexShader::VertexShader(tr::String src)
{
	_shader = glCreateShader(GL_VERTEX_SHADER);
	char* whythefuck = src.buf();
	glShaderSource(_shader, 1, &whythefuck, nullptr);
	glCompileShader(_shader);

	_check_compilation("vertex");
	tr::info("created vertex shader (id %u)", _shader);
}

void gsm::VertexShader::free()
{
	glDeleteShader(_shader);
	tr::info("deleted vertex shader (id %u)", _shader);
}

gsm::FragmentShader::FragmentShader(tr::String src)
{
	_shader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* whythefuck = src.buf();
	glShaderSource(_shader, 1, &whythefuck, nullptr);
	glCompileShader(_shader);

	_check_compilation("fragment");
	tr::info("created fragment shader (id %u)", _shader);
}

void gsm::FragmentShader::free()
{
	glDeleteShader(_shader);
	tr::info("deleted fragment shader (id %u)", _shader);
}

gsm::ShaderProgram::ShaderProgram()
{
	_program = glCreateProgram();
	tr::info("created shader program (id %u)", _program);
}

void gsm::ShaderProgram::free()
{
	glDeleteProgram(_program);
	tr::info("deleted shader program (id %u)", _program);
	_program = 0;
}

// 'Method can be made const'
// nuh uh they are, in fact, changing state
// NOLINTBEGIN(readability-make-member-function-const)
void gsm::ShaderProgram::attach(const gsm::Shader& shader)
{
	glAttachShader(_program, shader._shader);
}

void gsm::ShaderProgram::link()
{
	glLinkProgram(_program);

	int success;
	glGetProgramiv(_program, GL_LINK_STATUS, &success);
	if (success == 0) {
		char infolog[512];
		glGetProgramInfoLog(_program, 512, nullptr, infolog);
		tr::panic("gpu program linking error: %s", infolog);
	}

	tr::info("linked shader program (id %u)", _program);
}

void gsm::ShaderProgram::use()
{
	glUseProgram(_program);
}

void gsm::ShaderProgram::set_uniform(tr::String name, bool value)
{
	use();
	glUniform1i(glGetUniformLocation(_program, name), int(value));
}

void gsm::ShaderProgram::set_uniform(tr::String name, int32 value)
{
	use();
	glUniform1i(glGetUniformLocation(_program, name), value);
}

void gsm::ShaderProgram::set_uniform(tr::String name, uint32 value)
{
	use();
	glUniform1ui(glGetUniformLocation(_program, name), value);
}

void gsm::ShaderProgram::set_uniform(tr::String name, float32 value)
{
	use();
	glUniform1f(glGetUniformLocation(_program, name), value);
}

void gsm::ShaderProgram::set_uniform(tr::String name, tr::Vec2<float32> value)
{
	use();
	glUniform2f(glGetUniformLocation(_program, name), value.x, value.y);
}

void gsm::ShaderProgram::set_uniform(tr::String name, tr::Vec3<float32> value)
{
	use();
	glUniform3f(glGetUniformLocation(_program, name), value.x, value.y, value.z);
}

void gsm::ShaderProgram::set_uniform(tr::String name, tr::Vec4<float32> value)
{
	use();
	glUniform4f(glGetUniformLocation(_program, name), value.x, value.y, value.z, value.w);
}

void gsm::ShaderProgram::set_uniform(tr::String name, tr::Vec2<int32> value)
{
	use();
	glUniform2i(glGetUniformLocation(_program, name), value.x, value.y);
}

void gsm::ShaderProgram::set_uniform(tr::String name, tr::Vec3<int32> value)
{
	use();
	glUniform3i(glGetUniformLocation(_program, name), value.x, value.y, value.z);
}

void gsm::ShaderProgram::set_uniform(tr::String name, tr::Vec4<int32> value)
{
	use();
	glUniform4i(glGetUniformLocation(_program, name), value.x, value.y, value.z, value.w);
}

void gsm::ShaderProgram::set_uniform(tr::String name, tr::Vec2<uint32> value)
{
	use();
	glUniform2ui(glGetUniformLocation(_program, name), value.x, value.y);
}

void gsm::ShaderProgram::set_uniform(tr::String name, tr::Vec3<uint32> value)
{
	use();
	glUniform3ui(glGetUniformLocation(_program, name), value.x, value.y, value.z);
}

void gsm::ShaderProgram::set_uniform(tr::String name, tr::Vec4<uint32> value)
{
	use();
	glUniform4ui(glGetUniformLocation(_program, name), value.x, value.y, value.z, value.w);
}

void gsm::ShaderProgram::set_uniform(tr::String name, tr::Matrix4x4 value)
{
	use();
	// man
	glUniformMatrix4fv(
		glGetUniformLocation(_program, name), 1, 0u, reinterpret_cast<float32*>(&value)
	);
}
// NOLINTEND(readability-make-member-function-const)

tr::Result<gsm::Texture> gsm::Texture::load(tr::String path, TextureSettings settings)
{
	Texture texture = {};

	TR_TRY_ASSIGN(
		tr::File& file, tr::File::open(
					_gsm.asset_arena, tr::path(_gsm.asset_arena, path),
					tr::FileMode::READ_BINARY
				)
	);
	TR_DEFER(file.close());
	TR_TRY_ASSIGN(tr::Array<uint8> bytes, file.read_all_bytes(_gsm.asset_arena));

	// TODO texture cache
	// TODO gsm::Texture::from_memory()
	int width = 0;
	int height = 0;
	int channels = 0;
	uint8* data = stbi_load_from_memory(
		*bytes, static_cast<int>(bytes.len()), &width, &height, &channels, 4
	);
	if (data == nullptr) {
		return tr::StringError("couldn't load texture from %s", *path);
	}
	TR_DEFER(stbi_image_free(data));
	TR_ASSERT(width > 0 && height > 0 && channels > 0);

	glGenTextures(1, &texture._id);
	glBindTexture(GL_TEXTURE_2D, texture._id);

	// help
	switch (settings.wrap) {
	case TextureWrap::TILE:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		break;
	case TextureWrap::MIRRORED_TILE:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		break;
	case TextureWrap::CLAMP_TO_EDGE:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		break;
	case TextureWrap::CLAMP_TO_BORDER:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		break;
	default:
		TR_UNREACHABLE();
	}

	// TODO you're probably doing this wrong
	switch (settings.filter) {
	case TextureFilter::NEAREST_NEIGHBOR:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	case TextureFilter::BILINEAR_FILTER:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	default:
		TR_UNREACHABLE();
	}

	texture._size = {uint32(width), uint32(height)};
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	if (settings.mipmaps) {
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	tr::info("loaded texture from %s (id %u)", *path, texture._id);
	return texture;
}

void gsm::Texture::free()
{
	glDeleteTextures(1, &_id);
	tr::info("deleted texture (id %u)", _id);
	_id = 0;
}

void gsm::Texture::use() const
{
	TR_ASSERT_MSG(_id != 0, "you doofus initialize the texture")
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _id);
}
