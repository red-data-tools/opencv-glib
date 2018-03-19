class TestMatrix < Test::Unit::TestCase
  sub_test_case(".new") do
    def test_empty
      matrix = CV::Matrix.new
      assert do
        matrix.empty?
      end
    end
  end
end
