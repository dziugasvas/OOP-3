#include <gtest/gtest.h>
#include "Studentas.h"
#include "funkcijos.h"
#include <sstream>
#include <vector>

TEST(StudentasTest, DefaultConstructor) {
    Studentas s;
    EXPECT_TRUE(s.getVardas().empty());
    EXPECT_TRUE(s.getPavarde().empty());
    EXPECT_TRUE(s.getPaz().empty());
    EXPECT_EQ(s.getEgz(), 0);
    EXPECT_EQ(s.getRez(), 0.0);
}

TEST(StudentasTest, CopyConstructor) {
    Studentas s;
    s.setVardas("Tomas");
    s.setPavarde("Tomauskas");
    s.setPaz({5, 7, 8});
    s.setEgz(7);

    Studentas copy(s);
    EXPECT_EQ(copy.getVardas(), s.getVardas());
    EXPECT_EQ(copy.getPavarde(), s.getPavarde());
    EXPECT_EQ(copy.getPaz(), s.getPaz());
    EXPECT_EQ(copy.getEgz(), s.getEgz());

    copy.setVardas("Other");
    EXPECT_EQ(s.getVardas(), "Tomas");
}

TEST(StudentasTest, CopyAssignment) {
    Studentas s1;
    s1.setVardas("Lukas");
    s1.setPavarde("Lukauskas");
    s1.setPaz({4, 6, 9});
    s1.setEgz(8);

    Studentas s2;
    s2 = s1;
    EXPECT_EQ(s2.getVardas(), s1.getVardas());
    EXPECT_EQ(s2.getPaz(), s1.getPaz());

    s1 = s1;
    EXPECT_EQ(s1.getVardas(), "Lukas");
}

TEST(StudentasTest, MoveConstructor) {
    Studentas s;
    s.setVardas("Mantas");
    s.setPavarde("Mantauskas");
    s.setPaz({3, 6, 10});
    s.setEgz(6);

    Studentas moved(std::move(s));
    EXPECT_EQ(moved.getVardas(), "Mantas");
    EXPECT_EQ(moved.getEgz(), 6);

    EXPECT_TRUE(s.getVardas().empty());
    EXPECT_TRUE(s.getPaz().empty());
    EXPECT_EQ(s.getEgz(), 0);
}

TEST(StudentasTest, MoveAssignment) {
    Studentas s;
    s.setVardas("Erikas");
    s.setPavarde("Erikauskas");
    s.setPaz({7, 8, 10});
    s.setEgz(9);

    Studentas moved;
    moved = std::move(s);
    EXPECT_EQ(moved.getVardas(), "Erikas");
    EXPECT_EQ(moved.getEgz(), 9);
    EXPECT_TRUE(s.getVardas().empty());
}

TEST(StudentasTest, Destructor) {
    {
        Studentas s;
        s.setVardas("Temp");
        s.setPavarde("Tempauskas");
        s.setEgz(5);
        s.setPaz({1, 2, 3});
    }
    SUCCEED();
}

TEST(StudentasTest, InputOutputOperators) {
    std::stringstream input("Rokas Rokauskas 5 6 7 8\n");
    Studentas s;
    input >> s;
    EXPECT_EQ(s.getVardas(), "Rokas");
    EXPECT_EQ(s.getPavarde(), "Rokauskas");
    EXPECT_EQ(s.getPaz()[0], 5);
    EXPECT_EQ(s.getPaz()[1], 6);
    EXPECT_EQ(s.getPaz()[2], 7);
    EXPECT_EQ(s.getEgz(), 8);

    std::stringstream output;
    output << s;
    EXPECT_EQ(output.str(), "Rokas Rokauskas 5 6 7 8");
}

TEST(ZmogusTest, ZmogusAbstrakcija) {
    Studentas s;
    Zmogus& ref = s;
    ref.setVardas("Test");
    ref.setPavarde("Testauskas");
    EXPECT_EQ(ref.getVardas(), "Test");
    EXPECT_EQ(ref.getPavarde(), "Testauskas");
}

TEST(FunkcijosTest, Vidurkis) {
    std::vector<int> grades = {4, 6, 8, 10};
    EXPECT_DOUBLE_EQ(vidurkis(grades), 7.0);

    std::vector<int> empty = {};
    EXPECT_DOUBLE_EQ(vidurkis(empty), 0.0);
}

TEST(FunkcijosTest, Mediana) {
    std::vector<int> odd = {1, 3, 5};
    EXPECT_DOUBLE_EQ(mediana(odd), 3.0);

    std::vector<int> even = {1, 2, 3, 4};
    EXPECT_DOUBLE_EQ(mediana(even), 2.5);

    std::vector<int> empty = {};
    EXPECT_DOUBLE_EQ(mediana(empty), 0.0);
}

TEST(StudentasTest, GalutinisBalas) {
    Studentas s;
    s.setPaz({8, 8, 8});
    s.setEgz(8);
    s.setGalutinisVid(0.4 * vidurkis(s.getPaz()) + 0.6 * s.getEgz());
    EXPECT_NEAR(s.getGalutinisVid(), 8.0, 0.001);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
