## Умные указатели

### Unique pointer
Уникальный владеющий указатель на объект, при уничтожении которого вызывается 
деструктор хранимого объекта. Удобная штука для решения проблемы с утечкой памяти.
При этом не имеет конструктор копирования и оператора присвоения, за счет чего и
остается уникальным.

Задается через `unique_ptr<T>(new T)`, передается через `std::move(unique_ptr)`.

Может быть принят функцией by value или by rvalue reference:
```
std::unique_ptr<D> my_func(std::unique_ptr<D> p)
{
    p->bar();
    return p;
}
```

В случае вызова владение передастся в функцию my_func, после чего вернется через
return:
```
std::unique_ptr<D> q = pass_through(std::move(p));
```

[Пример использования](../src/smart_pointers/unique_ptr.cpp)

### Shared pointer
Схоже с unique pointer, но со счетчиком ссылок, то есть не уникален, можно копировать
и передавать присваиванием, что инкрементирует счетчик. Уничтожение указателя,
соответственно, уменьшает счетчик на 1. Как только счетчик достигнет нуля - 
хранимый объект удаляется.

[Пример использования](../src/smart_pointers/shared_ptr.cpp)

### Weak pointer
Не владеющий указатель на объект. Для доступа к хранимому объекту должен быть
сконвертирован в shared pointer (при этом счетчик shared pointer-а не увеличится.
Необходим для временного доступа к объекту, когда может быть удален кем-то из вне.
Так же позволяет обойти проблему утечки памяти при циклической зависимости:
```
class Human
{
	std::string m_name;
	std::shared_ptr<Human> m_partner; // изначально пустой
 
public:
		
	Human(const std::string &name): m_name(name)
	{ 
		std::cout << m_name << " created\n";
	}
	~Human()
	{
		std::cout << m_name << " destroyed\n";
	}
 
	friend bool partnerUp(std::shared_ptr<Human> &h1, std::shared_ptr<Human> &h2)
	{
		if (!h1 || !h2)
			return false;
 
		h1->m_partner = h2;
		h2->m_partner = h1;
 
		std::cout << h1->m_name << " is now partnered with " << h2->m_name << "\n";
 
		return true;
	}
};
 
int main()
{
	auto anton = std::make_shared<Human>("Anton"); // создание умного указателя с объектом Anton класса Human
	auto ivan = std::make_shared<Human>("Ivan"); // создание умного указателя с объектом Ivan класса Human
 
	partnerUp(anton, ivan); // Anton указывает на Ivan-а, а Ivan указывает на Anton-а
 
	return 0;
}
```
Запустив такой код, получим вывод:
```
Anton created
Ivan created
Anton is now partnered with Ivan
```
То есть объекты не удалятся, так как у объекта ivan сохранится указатель на anton и
наоборот. Получим утечку памяти. Решается эта проблема заменой внутри классов
shared_ptr на weak_ptr.

[Пример использования](../src/smart_pointers/weak_ptr.cpp)