
#include <array>
#include <deque>

#include <gmock/gmock.h>

#include <cppassist/algorithm/collect.h>
#include <unordered_set>


using namespace cppassist;
using namespace algorithm;


template <typename T>
struct Allocator : std::allocator<T>
{
};


template <typename T>
struct Greater
{
    bool operator()(const T & v1, const T & v2) const
    {
        return std::less<T>{}(v2, v1);
    }
};

template <typename T>
struct Hash
{
    std::size_t operator()(const T & v) const
    {
        return std::hash<T>{}(v);
    }
};

template <typename T>
struct EqualTo
{
    bool operator()(const T&  v1, const T & v2) const
    {
        return std::equal_to<T>{}(v1, v2);
    }
};


std::string convert_single(int value)
{
    return std::to_string(value);
}


std::initializer_list<int> m_initializerList{ -9198880, 96801928, 33316728, 80982026, 73853833, 99971965, 23515878, 6745749, 92276312, 98113098, 32261739, 21064214, 66415596, 133095, 10045572, 5303144, 22491772, 51711666, 70331437, 25908160, 31697032, 55834366, 35188552, 67849937, 98808105, 70907294, -9613997, 23250575, 95022988, 68193511, 87563398, 52809751, 36033138, 42154455, 54887718, -4039754, 57354576, 169149, 42665666, 97753461, 95360868, 96799748, 60700786, 20997325, 81748150, 16506436, 16077645, 51048746, 82137829, 79490438, 72783078, 45621069, 80713200, 51011807, -7803670, 3971706, 30664231, 14083839, 98095515, 45224232, 73251632, 41798654, 68831824, 48528297, 94830658, 78248670, -4161288, 53452001, 13000660, 37268037, 65307089, 1654799, 87138676, 47987886, 93797628, 81439532, 72113831, 28904197, 71551224, 56687182, 78956061, -4817618, 87974845, 11380998, 28235787, 85853654, 15441905, 76937671, 60102535, 95427036, 52138877, 40771972, 30374146, 16942904, 55758609, 25340282, 31111953, 98998649, 85201389, 20761381, 19655223, 76168045, 37289358, 78703112, 87174641, 98820755, 85008583, -9635965, -164978, 1313791, 52090956, -7295670, 33164976, 28568687, 51792151, -1561546, 43009793, 77908749, 61924982, 48174281, 92053179, 36754799, -6955856, 33115679, -9651549, 2999886, 32376221, 17128209, 18079733, 82986782, 55005738, 58598535, 47586971, 54237365, 60308088, 97016328, 2427944, -8381286, 65003999, 60459239, 61821067, 14338873, 19222313, 83714820, 29334109, 16987422, 5376509, 30367549, 14792497, 2753075, 87884628, 23664279, -5466075, 5393437, -8149813, 21355673, 76283021, -7437434, 25006615, -7764216, 66775240, 57181117, 60561716, 59417296, -1147023, 52726011, 68929290, 83047595, 6628231, 6524668, 42048630, 12388460, -2762535, 30174029, 97860929, 14496811, 35957725, -1681732, 12695404, 80044445, 55682481, 74229067, 14433306, 11217077, 9350579, -5575616, -1299904, 72222620, 34385541, 54913304, 39712414, 24065764, 59950211, 21276987, 19976760, 89318883, 10990521, 81703367, 29237646, 40192470, 37750981, 99903172, 73652026, 28048718, 3293911, 32934055, 71364647, -9126774, 13113372, -2953198, -8979185, 17896930, 97961542, 83883421, -4867150, 17922700, 27669503, 91621231, 8337023, 5249372, 72626043, 19944096, 72085111, 27342751, 97129062, 42551879, 53727192, 14282314, 45124548, 56623528, 92903288, 65505260, 58487895, 87055749, 68790587, 24672356, 44333757, 24434520, 29083787, 9515994, 2672843, 45266142, 38205545, 77599395, 74881379, 18595614, 76448122, 16860211, 1264825, 41152548, 3264856, 66538223, 78817687, -6165507, 5006250, 10285952 };


class collect_test : public testing::Test
{
public:
    collect_test()
    {
        auto arrayItr = m_array.begin();
        for (auto v : m_initializerList)
        {
            *arrayItr++ = v;
            m_vector.push_back(v);
            m_vectorAllocator.push_back(v);
            m_deque.push_back(v);
            m_dequeAllocator.push_back(v);
            m_list.push_back(v);
            m_listAllocator.push_back(v);
            m_set.insert(v);
            m_setGreater.insert(v);
            m_setGreaterAllocator.insert(v);
            m_unorderedSet.insert(v);
            m_unorderedSetHash.insert(v);
            m_unorderedSetHashEqualTo.insert(v);
            m_unorderedSetHashEqualToAllocator.insert(v);

            m_expectedList.push_back(convert_single(v));
            m_expectedSet.insert(convert_single(v));
        }
    }

protected:
    template <typename T>
    bool equalExpectedList(const T & container)
    {
        std::vector<std::string> actual{ container.begin(), container.end() };
        return m_expectedList == actual;
    }

    template <typename T>
    bool equalExpectedSet(const T & container)
    {
        std::set<std::string> actual{ container.begin(), container.end() };
        return m_expectedSet == actual;
    }

protected:
    std::vector<std::string> m_expectedList;
    std::set<std::string> m_expectedSet;

    std::array<int, 256> m_array;
    std::vector<int> m_vector;
    std::vector<int, Allocator<int>> m_vectorAllocator;
    std::deque<int> m_deque;
    std::deque<int, Allocator<int>> m_dequeAllocator;
    std::list<int> m_list;
    std::list<int, Allocator<int>> m_listAllocator;
    std::set<int> m_set;
    std::set<int, Greater<int>> m_setGreater;
    std::set<int, Greater<int>, Allocator<int>> m_setGreaterAllocator;
    // TODO
    std::unordered_set<int> m_unorderedSet;
    std::unordered_set<int, Hash<int>> m_unorderedSetHash;
    std::unordered_set<int, Hash<int>, EqualTo<int>> m_unorderedSetHashEqualTo;
    std::unordered_set<int, Hash<int>, EqualTo<int>, Allocator<int>> m_unorderedSetHashEqualToAllocator;
};


template <typename Expected, typename Container>
void static_assert_allocator(const Container &)
{
    static_assert(std::is_same<typename Container::allocator_type, Expected>::value, "Allocator type mismatch");
}


TEST_F(collect_test, vector_equal)
{
    const auto fromInitializerList     = collect<std::vector>(m_initializerList,     &convert_single);
    const auto fromVector              = collect<std::vector>(m_vector,              &convert_single);
    const auto fromVectorAllocator     = collect<std::vector>(m_vectorAllocator,     &convert_single);
    const auto fromDeque               = collect<std::vector>(m_deque,               &convert_single);
    const auto fromDequeAllocator      = collect<std::vector>(m_dequeAllocator,      &convert_single);
    const auto fromList                = collect<std::vector>(m_list,                &convert_single);
    const auto fromListAllocator       = collect<std::vector>(m_listAllocator,       &convert_single);
    const auto fromSet                 = collect<std::vector>(m_set,                 &convert_single);
    const auto fromSetGreater          = collect<std::vector>(m_setGreater,          &convert_single);
    const auto fromSetGreaterAllocator = collect<std::vector>(m_setGreaterAllocator, &convert_single);

    EXPECT_TRUE(equalExpectedList(fromInitializerList));
    EXPECT_TRUE(equalExpectedList(fromVector));
    EXPECT_TRUE(equalExpectedList(fromVectorAllocator));
    EXPECT_TRUE(equalExpectedList(fromDeque));
    EXPECT_TRUE(equalExpectedList(fromDequeAllocator));
    EXPECT_TRUE(equalExpectedList(fromList));
    EXPECT_TRUE(equalExpectedList(fromListAllocator));
    EXPECT_TRUE(equalExpectedSet(fromSet));
    EXPECT_TRUE(equalExpectedSet(fromSetGreater));
    EXPECT_TRUE(equalExpectedSet(fromSetGreaterAllocator));
}


TEST_F(collect_test, vector_source_allocator)
{
    const auto fromInitializerList     = collect<std::vector>(m_initializerList,     &convert_single);
    const auto fromVector              = collect<std::vector>(m_vector,              &convert_single);
    const auto fromVectorAllocator     = collect<std::vector>(m_vectorAllocator,     &convert_single);
    const auto fromDeque               = collect<std::vector>(m_deque,               &convert_single);
    const auto fromDequeAllocator      = collect<std::vector>(m_dequeAllocator,      &convert_single);
    const auto fromList                = collect<std::vector>(m_list,                &convert_single);
    const auto fromListAllocator       = collect<std::vector>(m_listAllocator,       &convert_single);
    const auto fromSet                 = collect<std::vector>(m_set,                 &convert_single);
    const auto fromSetGreater          = collect<std::vector>(m_setGreater,          &convert_single);
    const auto fromSetGreaterAllocator = collect<std::vector>(m_setGreaterAllocator, &convert_single);

    static_assert_allocator<std::allocator<std::string>>(fromInitializerList);
    static_assert_allocator<std::allocator<std::string>>(fromVector);
    static_assert_allocator<Allocator<std::string>>(fromVectorAllocator);
    static_assert_allocator<std::allocator<std::string>>(fromDeque);
    static_assert_allocator<std::allocator<std::string>>(fromDequeAllocator);
    static_assert_allocator<std::allocator<std::string>>(fromList);
    static_assert_allocator<std::allocator<std::string>>(fromListAllocator);
    static_assert_allocator<std::allocator<std::string>>(fromSet);
    static_assert_allocator<std::allocator<std::string>>(fromSetGreater);
    static_assert_allocator<std::allocator<std::string>>(fromSetGreaterAllocator);
}


TEST_F(collect_test, vector_result_allocator)
{
    const auto withCustomAllocator = collect<std::vector, Allocator>(m_vector, &convert_single);
    const auto withStdAllocator    = collect<std::vector, std::allocator>(m_vectorAllocator, &convert_single);

    static_assert_allocator<Allocator<std::string>>(withCustomAllocator);
    static_assert_allocator<std::allocator<std::string>>(withStdAllocator);
}


TEST_F(collect_test, vector_same_type)
{
    const auto fromVector          = collect(m_vector, &convert_single);
    const auto fromVectorAllocator = collect(m_vectorAllocator, &convert_single);

    static_assert_allocator<std::allocator<std::string>>(fromVector);
    static_assert_allocator<Allocator<std::string>>(fromVectorAllocator);

    EXPECT_TRUE(equalExpectedList(fromVector));
    EXPECT_TRUE(equalExpectedList(fromVectorAllocator));
}
