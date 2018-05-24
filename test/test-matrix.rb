class TestMatrix < Test::Unit::TestCase
  sub_test_case(".new") do
    def test_empty
      matrix = CV::Matrix.new
      assert do
        matrix.empty?
      end
    end
  end

  sub_test_case("instance methods") do
    sub_test_case("#bytes") do
      def test_empty
        matrix = CV::Matrix.new
        assert_equal("", matrix.bytes.to_s)
      end
    end
  end
end
