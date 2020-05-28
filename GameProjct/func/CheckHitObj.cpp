#include <func/CheckHitObj.h>

Vector2Template<double> CheckHitObj::operator()(Vector2Template<double> obj_pos, Vector2Template<int> obj_size, OBJ_TYPE ignore_objtype, std::shared_ptr<object> ignore_obj, CHECK_DIR dir)
{	
	for (auto data : GameScene::_objList)
	{
		if (data->getType() != ignore_objtype && data != ignore_obj)
		{
			Vector2Template<double> cubePos = data->getPos();
			Vector2Template<int> cubeSize = data->getSize();
			switch (dir)
			{
			case CHECK_DIR::UP:
				if ((obj_pos.y >= cubePos.y && obj_pos.y < cubePos.y + cubeSize.y) &&
					((obj_pos.x >= cubePos.x && obj_pos.x < cubePos.x + cubeSize.x) || (obj_pos.x + obj_size.x - 1 >= cubePos.x && obj_pos.x + obj_size.x - 1 < cubePos.x + cubeSize.x)))
				{
					return cubePos;
				}
				break;
			case CHECK_DIR::DOWN:
				if ((obj_pos.y + obj_size.y >= cubePos.y && obj_pos.y + obj_size.y < cubePos.y + cubeSize.y) &&
					((obj_pos.x >= cubePos.x && obj_pos.x < cubePos.x + cubeSize.x) || (obj_pos.x + obj_size.x - 1 >= cubePos.x && obj_pos.x + obj_size.x - 1 < cubePos.x + cubeSize.x)))
				{
					return cubePos;
				}
				break;
			case CHECK_DIR::LEFT:
				if ((obj_pos.x >= cubePos.x && obj_pos.x < cubePos.x + cubeSize.x) &&
					((obj_pos.y >= cubePos.y && obj_pos.y < cubePos.y + cubeSize.y) || (obj_pos.y + obj_size.y - 1 >= cubePos.y && obj_pos.y + obj_size.y - 1 < cubePos.y + cubeSize.y)))
				{
					return cubePos;
				}
				break;
			case CHECK_DIR::RIGHT:
				if ((obj_pos.x + obj_size.x - 1 >= cubePos.x && obj_pos.x + obj_size.x - 1 < cubePos.x + cubeSize.x) &&
					((obj_pos.y >= cubePos.y && obj_pos.y < cubePos.y + cubeSize.y) || (obj_pos.y + obj_size.y - 1 >= cubePos.y && obj_pos.y + obj_size.y - 1 < cubePos.y + cubeSize.y)))
				{
					return cubePos;
				}
				break;
			default:
				AST();
				break;
			}
		}
	}
	return {-100,-100};
}
