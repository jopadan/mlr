
	namespace geo
	{

		template<typ::sca T, GLenum primitive_type, GLenum winding>
			struct box;

		template<typ::sca T, GLenum primitive_type, GLenum winding>
			std::ostream& operator<<(std::ostream& stream, const box<T, primitive_type, winding>& rhs)
			{
				for(size_t i = 0; i < rhs.vertices.size(); i++)
					stream << "[" << i << "]: " << rhs.vertices[i] << " normal: " << rhs.normals[i] << std::endl;
				for(size_t i = 0; i < rhs.indices.size(); i++)
					stream << rhs.indices[i] << std::endl;
				for(size_t i = 0; i < rhs.face_centers.size(); i++)
					stream << rhs.face_centers[i] << std::endl;
				for(size_t i = 0; i < rhs.face_normals.size(); i++)
					stream << rhs.face_normals[i] << std::endl;
				for(size_t i = 0; i < rhs.face_normal_vertices.size(); i++)
					stream << rhs.face_normal_vertices[i] << " " << rhs.face_normal_vertices[i].as_direction().len() << std::endl;
				for(size_t i = 0; i < rhs.vertex_normal_vertices.size(); i++)
					stream << rhs.vertex_normal_vertices[i] << " " << rhs.vertex_normal_vertices[i].as_direction().len() << std::endl;
				return stream;
			}

		template<typ::sca T, GLenum primitive_type, GLenum winding>
			struct box
			{
				vec4<T> pos;
				vec4<T> ext;
				std::array<vec4<T>, 8> vertices;
				std::array<vec4<T>, 8> normals;
				std::array<vec4<T>, 8> colors;
				std::array<vec4<T>, 8> texcoords;
				std::array<vec4<T>, 6> face_normals;
				std::array<vec4<T>, 6> face_centers;
				std::array<vec4<T>, 12> face_normal_vertices;
				std::array<vec4<T>, 16> vertex_normal_vertices;
				std::conditional_t<primitive_type == GL_QUADS, std::array<vec4<idx8>, 6>, std::array<vec4<idx8>, 6 * 2>> indices;

				box(vec4<T> _pos = { 0.0f, 0.0f, 0.0f, 0.0f }, vec4<T> _ext = { 0.5f, 0.5f, 0.5f, 0.0f }) : pos(_pos), ext(_ext)
				{
					generate();
				}
				void generate()
				{
					/*
					   if(i % 4 == 0)
					   {
					   vertices[i].pos = ((i < (vertices.size() >> 2)) ? ext : -ext) * vec4<T>::one(i % 3) + vec4<T>::one(3);
					   hub_acc++;
					   }
					   else
					   */
					/* generate cube vertices octant based */
					idx hub_acc = 0;
					for(idx8 i = 0; i < vertices.size(); i++)
					{
						vertices[i] = 
						{
							(((i - hub_acc) & (1 << 2)) != 0 ? ext[0] : -ext[0]),
							(((i - hub_acc) & (1 << 1)) != 0 ? ext[1] : -ext[1]),
							(((i - hub_acc) & (1 << 0)) != 0 ? ext[2] : -ext[2]),
							1	
						};
						vertices[i] += pos;
						normals[i]   = (vertices[i].as_direction().normalized() - vertices[i].as_direction()).normalize();
						vertex_normal_vertices[(i << 1) + 0] = vertices[i].as_position();
						vertex_normal_vertices[(i << 1) + 1] = normals[i].as_position();
					}
					/* generate cube indices */
					switch(primitive_type)
					{
						case GL_QUADS:
							{
								indices[0] = { 4, 0, 2, 6 };
								indices[1] = { 1, 5, 7, 3 }; 
								indices[2] = { 0, 1, 3, 2 };
								indices[3] = { 5, 4, 6, 7 };
								indices[4] = { 5, 1, 0, 4 };
								indices[5] = { 6, 2, 3, 7 };
								break;
							}
						case GL_TRIANGLES:
							{
								const idx8 beg = 0;
								const idx8 end = 7;
								for(idx8 i = 0; i < 3; i++)
								{
									idx8 v1 = 1 << i;
									idx8 v2 = (v1 == 4) ? 1 : v1 << 1;

									indices[(i << 2) + 0] = { beg            ,       v1,       v2, 0 };
									indices[(i << 2) + 1] = { beg + (v1 + v2),       v2,       v1, 0 };
									indices[(i << 2) + 2] = { end            , end - v2, end - v1, 0 };
									indices[(i << 2) + 3] = { end - (v1 + v2), end - v1, end - v2, 0 };
								}
								break;
							}
						default:
							break;
					}
					/* generate face normals and centers */
					for(size_t i = 0, j = 2; i < face_normals.size(); j+=((i%2) * (j%3)), i++)
					{
						face_centers[i]    = vec4<T>::zero();
						face_centers[i][j] = (((i % 2) == 0) ? -ext[j % 3] : ext[j % 3]);
						face_normals[i]    = (face_centers[i].as_direction().normalized() - face_centers[i].as_direction()).normalize();
						face_normal_vertices[(i << 1) + 0] = face_centers[i].as_position();
						face_normal_vertices[(i << 1) + 1] = face_normals[i].as_position(); 
					}
				}

				void draw()
				{
					glPushMatrix();
					glEnable(GL_CULL_FACE);
					glFrontFace(GL_CCW);
					glCullFace(GL_BACK);
					glShadeModel(GL_SMOOTH);
					glEnable(GL_COLOR_MATERIAL);

					glEnableClientState(GL_TEXTURE_COORD_ARRAY);
					glEnableClientState(GL_COLOR_ARRAY);
					glEnableClientState(GL_NORMAL_ARRAY);
					glEnableClientState(GL_VERTEX_ARRAY);

					glTexCoordPointer(4, GL_FLOAT, 0, texcoords.data());
					glNormalPointer(GL_FLOAT, 1, normals.data());
					glColorPointer(4, GL_FLOAT, 0, vertices.data());
					glVertexPointer(4, GL_FLOAT, 0, vertices.data());

					glDrawElements(primitive_type, indices.size() * sizeof(vec::idx8<4>), GL_UNSIGNED_BYTE, indices.data());
					glDisableClientState(GL_TEXTURE_COORD_ARRAY);
					glDisableClientState(GL_COLOR_ARRAY);
					glDisableClientState(GL_NORMAL_ARRAY);
					glVertexPointer(4, GL_FLOAT, 0, face_normal_vertices.data());
					glDrawArrays(GL_LINES, 0, face_normal_vertices.size());
					glVertexPointer(4, GL_FLOAT, 0, vertex_normal_vertices.data());
					glDrawArrays(GL_LINES, 0, vertex_normal_vertices.size());

					glDisableClientState(GL_VERTEX_ARRAY);

					glPopMatrix();
				}

				friend std::ostream& operator<< <>(std::ostream& stream, const box<T,primitive_type, winding>& rhs);
};
};
};
