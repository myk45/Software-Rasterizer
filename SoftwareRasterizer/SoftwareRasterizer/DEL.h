struct Matrix3 {
		float m[3][3];

		Matrix3() {
			Identity();
		}

		Matrix3& Identity() {
			for(int i = 0; i < 3; i++)
				for(int j = 0; j < 3; j++)
					m[i][j] = (i == j);
			return *this;
		}

		Matrix3& Multiply(Matrix3& m2) {
			float p[3][3];
			for(int i = 0; i < 3; i++)
				for(int j = 0; j < 3; j++) {
					p[i][j] = 0;
					for(int k = 0; k < 3; k++)
						p[i][j] += m2.m[i][k] * m[k][j];
				}
			for(int i = 0; i < 3; i++)
				for(int j = 0; j < 3; j++)
					m[i][j] = p[i][j];
			return *this;
		}

		Matrix3& Scale(float sx, float sy) {
			Matrix3 s;
			s.m[0][0] = sx;
			s.m[1][1] = sy;

			return Multiply(s);
		}

		Matrix3& Translate(float tx, float ty) {
			Matrix3 t;
			t.m[0][2] = tx;
			t.m[1][2] = ty;

			return Multiply(t);
		}

		float NewX(float x, float y) {
			return m[0][0] * x + m[0][1] * y + m[0][2];
		}

		float NewY(float x, float y) {
			return m[1][0] * x + m[1][1] * y + m[1][2];
		}

		void Viewport(float xmin, float ymin, float xmax, float ymax, int width, int height) {
			float sx = width / (xmax - xmin), sy = height / (ymax - ymin);
			Identity().Translate(-xmin, -ymin).Scale(width / (xmax - xmin), height / (ymax - ymin));
		}
	};