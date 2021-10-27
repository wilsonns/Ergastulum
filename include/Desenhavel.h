class Entidade;

class Desenhavel
{
 private:
  char _simbolo;
  Entidade* self = nullptr;
 public:
  Desenhavel(char simbolo, Entidade* self);
  ~Desenhavel();
  void render(int x, int y);
  char simbolo();

}
