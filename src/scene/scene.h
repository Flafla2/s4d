
#pragma once

#include "../lib/math.h"
#include "../lib/gl.h"
#include "../lib/camera.h"

#include "scene_object.h"

#include <map>

class App;
class Scene {
public:
	Scene(Vec2 window_dim, App& app);
	~Scene();

	void render();
	void gui();

	void apply_window_dim(Vec2 new_dim);
	void add_object(Scene_Object&& obj);

	void camera_orbit(Vec2 dmouse);
	void camera_move(Vec2 dmouse);
	void camera_radius(float dmouse);
	void mouse_pos(Vec2 mouse);
	bool select(Vec2 mouse);

	void reload_shaders();
	void show_settings();

private:
	App& app;

	// Camera 
	Camera camera;
	Mat4 view, proj, viewproj;
	
	// GL data
	static const int default_samples = 4;
	int samples = default_samples;
	GL::Shader mesh_shader, line_shader;
	GL::Framebuffer framebuffer, id_resolve;
	
	// Baseplane
	void create_baseplane();
	GL::Lines baseplane;
	
	// Picking
	Scene_Object::ID read_id(Vec2 pos);
	float* id_buffer = nullptr;

	// GUI
	struct Gui {
		enum class Axis {
			X, Y, Z
		};
		enum class Action {
			move, rotate, scale
		};
		enum class Basic : Scene_Object::ID {
			none,
			x_trans, y_trans, z_trans,
			x_rot, y_rot, z_rot,
			x_scale, y_scale, z_scale,
			count
		};
		Vec2 window_dim;
		bool settings_open = false;
		
		bool selecting = false;
		Action action = Action::move;
		Axis axis = Axis::X;
		Scene_Object::ID id = (Scene_Object::ID)Basic::none;

		Scene_Object x_trans, y_trans, z_trans, x_rot, y_rot, z_rot, x_scale, z_scale, y_scale;
	};
	Gui state;
	void render_widgets(const Scene_Object& obj);

	// User Objects
	std::map<Scene_Object::ID, Scene_Object> objs;
	Scene_Object::ID next_id = (Scene_Object::ID)Gui::Basic::count;
};

