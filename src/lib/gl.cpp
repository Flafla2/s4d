	
#include "gl.h"
#include "log.h"

#include <fstream>

GL_Mesh::GL_Mesh() {
	create();
}

GL_Mesh::GL_Mesh(const std::vector<Vert>& vertices) {
	create();
	update(vertices);
}

GL_Mesh::GL_Mesh(GL_Mesh&& src) {
	vao = src.vao; src.vao = 0;
	vbo = src.vbo; src.vbo = 0;
	n_elem = src.n_elem; src.n_elem = 0;
}

GL_Mesh::~GL_Mesh() {
	destroy();
}

void GL_Mesh::create() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), (GLvoid*)sizeof(Vec3));
	glEnableVertexAttribArray(1);
	
	glBindVertexArray(0);
}

void GL_Mesh::destroy() {
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	vao = vbo = 0;
}

void GL_Mesh::update(const std::vector<Vert>& vertices) {

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);

	n_elem = vertices.size();
}

void GL_Mesh::render() {

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, n_elem);
	glBindVertexArray(0);
}

GL_Lines::GL_Lines(float thickness) : thickness(thickness) {
	create();
}

GL_Lines::GL_Lines(GL_Lines&& src) {
	dirty = src.dirty; src.dirty = false;
	thickness = src.thickness; src.thickness = 0.0f;
	vao = src.vao; src.vao = 0;
	vbo = src.vbo; src.vbo = 0;
	vertices = std::move(src.vertices);
}

GL_Lines::~GL_Lines() {
	destroy();
}

void GL_Lines::update() {

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Line_Vert) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glBindVertexArray(0);

	dirty = false;
}

void GL_Lines::render() {

	if(dirty) update();

	glLineWidth(thickness);
	glEnable(GL_LINE_SMOOTH);

	glBindVertexArray(vao);
	glDrawArrays(GL_LINES, 0, vertices.size());
	glBindVertexArray(0);
}

void GL_Lines::add(Vec3 start, Vec3 end, Vec3 color) {

	vertices.push_back({start, color});
	vertices.push_back({end, color});
	dirty = true;
}

void GL_Lines::create() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Line_Vert), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Line_Vert), (GLvoid*)sizeof(Vec3));
	glEnableVertexAttribArray(1);
	
	glBindVertexArray(0);
}

void GL_Lines::destroy() {
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	vao = vbo = 0;
	vertices.clear();
	dirty = false;
}

GL_Shader::GL_Shader(std::string vertex, std::string fragment) {
    load(vertex, fragment);
}

GL_Shader::GL_Shader(GL_Shader&& src) {
	v_file = std::move(src.v_file);
	f_file = std::move(src.f_file);
	program = src.program; src.program = 0;
	v = src.v; src.v = 0;
	f = src.f; src.f = 0;
}

GL_Shader::~GL_Shader() {
    destroy();
}

void GL_Shader::bind() {
    glUseProgram(program);
}

void GL_Shader::reload() {
	destroy();
	load(v_file, f_file);
}

void GL_Shader::destroy() {
	glUseProgram(0);
	glDeleteShader(v);
	glDeleteShader(f);
	glDeleteProgram(program);
	v = f = program = 0;
}

GLuint GL_Shader::uniform(std::string name) const {

    return glGetUniformLocation(program, name.c_str());
}

void GL_Shader::load(std::string vertex, std::string fragment) {

	v_file = vertex;
	f_file = fragment;
	std::string vs, fs;
	std::ifstream vfin(vertex), ffin(fragment);
	std::getline(vfin, vs, '\0');
	std::getline(ffin, fs, '\0');

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* vs_c = vs.c_str();
	const GLchar* fs_c = fs.c_str();
	glShaderSource(v, 1, &vs_c, NULL);
	glShaderSource(f, 1, &fs_c, NULL);
	glCompileShader(v);
	glCompileShader(f);

	if(!validate(v)) {
        destroy();
        return;
    }
	if(!validate(f)) {
        destroy();
        return;
    }

	program = glCreateProgram();
	glAttachShader(program, v);
	glAttachShader(program, f);
	glLinkProgram(program);
}

bool GL_Shader::validate(GLuint program) {

	GLint compiled = 0;
	glGetShaderiv(program, GL_COMPILE_STATUS, &compiled);
	if(compiled == GL_FALSE) {
		
		GLint len = 0;
		glGetShaderiv(program, GL_INFO_LOG_LENGTH, &len);

		GLchar* msg = new GLchar[len];
		glGetShaderInfoLog(program, len, &len, msg);

		warn("Shader %d failed to compile: %s", program, msg);
		delete[] msg;

        return false;
	}
    return true;
}

