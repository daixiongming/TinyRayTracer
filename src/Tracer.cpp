#include "Tracer.h"

Tracer::Tracer()
:_pixel_nx(640), _pixel_ny(480),
_viewport_left(-0.1), _viewport_right(0.1), _viewport_top(0.1), _viewport_bottom(-0.1),
_camera_u(1.0, 0.0, 0.0), _camera_v(0.0, 0.0, 1.0), _camera_w(0.0, -1.0, 0.0),
_camera_pos(0.0, 0.0, 1.0),
_perspective(true)
{

}

void Tracer::trace()
{
	
}

void Tracer::computeRay(int x, int y, Vector3d& direction, Vector3d& origin)
{
	double u = _viewport_left + (_viewport_right - _viewport_left)*(x + 0.5) / _pixel_nx;
	double v = _viewport_bottom + (_viewport_top - _viewport_bottom)*(y + 0.5) / _pixel_ny;
	if (_perspective){
		direction = -_fd * _camera_w + u * _camera_u + v * _camera_v;
		origin = _camera_pos;
	}else{
		direction = -_camera_w;
		origin = _camera_pos + u * _camera_u + v * _camera_v;
	}
}