#include <cstdlib>
#include <iomanip>
#include <iostream>

class Sat {
  int sati, minute, sekunde;
  static const int dan = 86400; // broj sekundi
public:
  Sat();
  Sat(int sati, int minute, int sekunde);
  void PostaviNormalizirano(int sati, int minute, int sekunde);
  int DajSate() const;
  int DajMinute() const;
  int DajSekunde() const;
  friend Sat &operator++(Sat &sat);
  friend Sat operator++(Sat &sat, int);
  friend Sat &operator--(Sat &sat);
  friend Sat operator--(Sat &sat, int);
  friend Sat operator+(Sat &sat, int sek);
  friend Sat operator-(Sat &sat, int sek);
  friend Sat operator+=(Sat &sat, int sek);
  friend Sat operator-=(Sat &sat, int sek);
  friend int operator-(const Sat &sat1, const Sat &sat2);
  friend std::ostream &operator<<(std::ostream &tok, const Sat&sat);
};

void Sat::PostaviNormalizirano(int sati, int minute, int sekunde) {
  int temp = sati * 3600 + minute * 60 + sekunde;
  if (temp >= dan)
    temp = temp % dan; // ako smo 'prekoracili' dan
  if (temp < 0)
    temp = dan + temp % dan; // u slucaju da imamo negativan pomak (vrijeme)
  this->sati = temp / 3600;
  this->minute = (temp % 3600) / 60;
  this->sekunde = temp % 60;
}
Sat::Sat() : sati(0), minute(0), sekunde(0) {}
Sat::Sat(int sati, int minute, int sekunde)
  : sati(sati), minute(minute), sekunde(sekunde) {
  PostaviNormalizirano(sati, minute, sekunde);
}

int Sat::DajSate() const { return sati; }
int Sat::DajMinute() const { return minute; }
int Sat::DajSekunde() const { return sekunde; }


int operator-(const Sat &sat1, const Sat &sat2) {
  int vrijeme1 = sat1.DajSate() * 3600 + sat1.DajMinute() * 60 + sat1.DajSekunde();
  int vrijeme2 = sat2.DajSate() * 3600 + sat2.DajMinute() * 60 + sat2.DajSekunde();
  return vrijeme1 - vrijeme2;
}

Sat operator +(Sat &sat1, int sek) {
  Sat sat2(sat1.sati, sat1.minute, sat1.sekunde + sek);
  return sat2;
}
Sat operator -(Sat &sat, int sek) {
  Sat sat2(sat.sati, sat.minute, sat.sekunde - sek);
  return sat2;
}
Sat operator+=(Sat &sat, int sek) {
  sat.sekunde += sek;
  sat.PostaviNormalizirano(sat.sati, sat.minute, sat.sekunde);
  return sat;
}
Sat operator-=(Sat &sat, int sek) {
  sat.sekunde -= sek;
  sat.PostaviNormalizirano(sat.sati, sat.minute, sat.sekunde);
  return sat;
}
std::ostream &operator<<(std::ostream &tok, const Sat&sat) {
  tok << std::setw(2) << std::setfill('0') << sat.sati << ":";
  tok << std::setw(2) << std::setfill('0') << sat.minute ;
  return tok;
}


int main() {
    ponovo:
  int h1, h2, m1, m2; char znak;
  std::cout << "Format of enter: hours minutes\n";
  std::cout << "Enter sunset time: ";
  std::cin >> h1 >> m1;
  std::cout << "Enter real dawn time: ";
  std::cin >> h2 >> m2;
  Sat s1(h1, m1, 0);
  Sat s2(h2, m2, 0);
  Sat s(0, 0, 0);
  Sat ss = s2;
  int zbir1 = h1 * 3600 + m1 * 60;
  s -= zbir1;
  int zbir2 = s.DajSate() * 3600 + s.DajMinute() * 60 + s.DajSekunde();
  ss += zbir2;
  int zbir3 = ss.DajSate() * 3600 + ss.DajMinute() * 60 + ss.DajSekunde();
  Sat polovina = s1, trecina = s1;
  polovina += (zbir3 / 2);
  std::cout << "Half of night beginns at: " << polovina << std::endl;
  trecina += 2 * (zbir3 / 3);
  std::cout << "Last third of night beginns at: " << trecina << std::endl;
  std::cout<<"----------------------\n";
  std::cout<<"Restart program y/n: ";
  std::cin>>znak;
  if(znak=='y'||znak=='Y'){
        std::cout<<"\n";
     goto ponovo;
  }

  return 0;
}
