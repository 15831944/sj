#model(
	update(sceneRect : 'rect, projection : 'mat4, view : 'mat4, world : 'mat4, light : 'light)'void
	getZ()'f32
	renderOrQueue(zqueue : 'list!#model)'void
	render()'void
	fireMouseEvent(point: 'point, eventId : 'i32)'void
)

model_zsort(l : '#model, r : '#model) {
	f32_compare(l.getZ(), r.getZ())
}

model #model (
	vertexBuffer : 'vertexBuffer!vertex_location_texture_normal
	shader : 'shader
	texture : 'texture
	model : mat4_identity()
	center : vec3()
	hasAlpha : false
	id : string()
	_projection := mat4()
	_view := mat4()
	_world := mat4()
	_light := light()
	_projectedCenter := vec3()

	update(sceneRect : 'rect, projection : 'mat4, view : 'mat4, world : 'mat4, light : 'light)'void {
		_projection = copy projection
		_view = copy view
		_world = copy world
		t : _view * _world * model
		t2 : t.multiplyVec4(vec4(center.x, center.y, center.z, 1.0f))
		_projectedCenter = vec3(t2.x / t2.w, t2.y / t2.w, t2.z / t2.w)
		_light = copy light
		void
	}

	getZ() {
		_projectedCenter.z
	}

	renderOrQueue(zqueue : 'list!#model) {
		if hasAlpha {
			zqueue.add(heap parent as #model)
		} else {
			render()
		}
	}

	render()'void {
		world : _world * model
		viewWorld : _view * world
		normalMat : viewWorld.invert().transpose()
        glUseProgram(shader);
        glBindTexture(glTexture.GL_TEXTURE_2D, texture)
        glUniformMat4(glGetUniformLocation(shader, "viewModel"), viewWorld)
        glUniformMat4(glGetUniformLocation(shader, "normalMat"), normalMat)
        glUniformMat4(glGetUniformLocation(shader, "projection"), _projection)
        glUniformVec3(glGetUniformLocation(shader, "lightPos"), _light.pos)
        glUniformVec3(glGetUniformLocation(shader, "diffuseColor"), _light.diffuseColor.asVec3())
        glUniformVec3(glGetUniformLocation(shader, "specColor"), _light.specColor.asVec3())
		vertexBuffer.render()
	}

	fireMouseEvent(point: 'point, eventId : 'i32)'void {

	}
) { this }