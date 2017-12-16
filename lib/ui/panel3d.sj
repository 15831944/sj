panel3d #model(
	model : mat4_identity()
	children : array!#model()

	update(sceneRect : 'rect, projection : 'mat4, view : 'mat4, world : 'mat4, light : 'light)'void {
		childWorld : world * model 
		for i : 0 to children.count {
			c : children[i]
			c.update(sceneRect, projection, view, childWorld, light)
		}
		void
	}

	getZ() {
		0.0f
	}

	renderOrQueue(zqueue : 'list!#model)'void {
		for i : 0 to children.count {
			c : children[i]
			c.renderOrQueue(zqueue)
		}
	}

	render()'void {

	}

	fireMouseEvent(point: 'point, eventId : 'i32)'void {
		for i : 0 to children.count {
			c : children[i]
			c.fireMouseEvent(point, eventId)
		}
	}
) { this }