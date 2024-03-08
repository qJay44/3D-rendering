#include <cstdio>
#include <stdexcept>

// Assuming theres only 3x3 and 3x1 matrices
template<int R, int C>
struct mat {
  double m[R * C];

  void multiply(double rhs[]) const {
    if (C != 3)
      throw std::runtime_error("Invalid matrices shapes to multiply");

    mat<3, 1> result;

    for (int i = 0; i < R; i++) { // Every left side row (this->m)
      for (int j = 0; j < 1; j++) { // Every right side columns (rhs.m)
        double sum = 0.f;
        for (int k = 0; k < C; k++) { // Every left side column (this->m)
          const double& left = m[i * C + k];
          const double& right = rhs[k * 1 + j];
          sum += left * right;
        }
        result.m[i * 1 + j] = sum;
      }
    }

    for (int i = 0; i < 3; i++)
      rhs[i] = result.m[i];
  }

  void rotateX(double angle) {
    mat<3, 3> rotation {
      1., 0., 0.,
      0., cos(angle), -sin(angle),
      0., sin(angle),  cos(angle),
    };

    rotation.multiply(m);
  }

  void rotateY(double angle) {
    mat<3, 3> rotation {
      cos(angle), 0.,sin(angle),
      0., 1., 0.,
      -sin(angle), 0., cos(angle),
    };

    rotation.multiply(m);
  }

  void rotateZ(double angle) {
    mat<3, 3> rotation {
      cos(angle), -sin(angle), 0.,
      sin(angle),  cos(angle), 0.,
      0., 0., 1.
    };

    rotation.multiply(m);
  }

  void project() {
    static const mat<3, 3> projection {
      1., 0., 0.,
      0., 1., 0.,
      0., 0., 1.
    };

    projection.multiply(m);
  }

  void print() const {
    printf("{\n");
    for (int i = 0; i < R; i++) {
      printf("\t");
      for (int j = 0; j < C; j++) {
        printf("%f, ", m[i * C + j]);
      }
      printf("\n");
    }
    printf("}\n");
  }
};

