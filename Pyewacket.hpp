#pragma once
#include <algorithm>
#include <cmath>
#include <limits>
#include <random>


namespace Storm { // Storm 3.2.2 Custom
    using Integer = long long;
    
    namespace Engine {
        struct Cyclone {
            using MT64_SCRAM = std::shuffle_order_engine<std::discard_block_engine<std::mt19937_64, 12, 8>, 256>;
            std::random_device hardware_seed;
            MT64_SCRAM hurricane { hardware_seed() };
            template <typename D>
            auto operator()(D distribution) {
                return distribution(hurricane);
            }
            auto seed(unsigned long long seed) -> void {
                MT64_SCRAM seeded_storm { seed == 0 ? hardware_seed() : seed };
                hurricane = seeded_storm;
            }
        } cyclone;
    }

    auto canonical_variate() -> double {
        return std::generate_canonical<double, std::numeric_limits<double>::digits>(Engine::cyclone.hurricane);
    }

    auto uniform_real_variate(double a, double b) -> double {
        std::uniform_real_distribution<double> distribution { a, b };
        return Engine::cyclone(distribution);
    }

    auto uniform_int_variate(Storm::Integer a, Storm::Integer b) -> Storm::Integer {
        std::uniform_int_distribution<Storm::Integer> distribution { std::min(a, b), std::max(b, a) };
        return Engine::cyclone(distribution);
    }

    auto exponential_variate(double lambda_rate) -> double {
        std::exponential_distribution<double> distribution { lambda_rate };
        return Engine::cyclone(distribution);
    }

    auto gamma_variate(double shape, double scale) -> double {
        std::gamma_distribution<double> distribution { shape, scale };
        return Engine::cyclone(distribution);
    }

    auto weibull_variate(double shape, double scale) -> double {
        std::weibull_distribution<double> distribution { shape, scale };
        return Engine::cyclone(distribution);
    }

    auto normal_variate(double mean, double std_dev) -> double {
        std::normal_distribution<double> distribution { mean, std_dev };
        return Engine::cyclone(distribution);
    }

    auto lognormal_variate(double log_mean, double log_deviation) -> double {
        std::lognormal_distribution<double> distribution { log_mean, log_deviation };
        return Engine::cyclone(distribution);
    }

    auto random_below(Storm::Integer number) -> Storm::Integer {
        return Storm::uniform_int_variate(0, std::nextafter(number, 0));
    }

    auto random_range(Storm::Integer start, Storm::Integer stop, Storm::Integer step) -> Storm::Integer {
        if (start == stop or step == 0) return start;
        const auto width { std::abs(start - stop) - 1 };
        const auto pivot { step > 0 ? std::min(start, stop) : std::max(start, stop) };
        const auto step_size { std::abs(step) };
        return pivot + step_size * Storm::random_below((width + step_size) / step);
    }

    auto beta_variate(double alpha, double beta) -> double {
        const auto y { Storm::gamma_variate(alpha, 1.0) };
        if (y == 0.0) return 0.0;
        return y / (y + Storm::gamma_variate(beta, 1.0));
    }

    auto pareto_variate(double alpha) -> double {
        const auto u { 1.0 - Storm::canonical_variate() };
        return 1.0 / std::pow(u, 1.0 / alpha);
    }

    auto vonmises_variate(double mu, double kappa) -> double {
        static const double PI { 4 * std::atan(1) };
        static const double TAU { 8 * std::atan(1) };
        if (kappa <= 0.000001) return TAU * Storm::canonical_variate();
        const double s { 0.5 / kappa };
        const double r { s + std::sqrt(1 + s * s) };
        double u1 {0};
        double z {0};
        double d {0};
        double u2 {0};
        while (true) {
            u1 = Storm::canonical_variate();
            z = std::cos(PI * u1);
            d = z / (r + z);
            u2 = Storm::canonical_variate();
            if (u2 < 1.0 - d * d or u2 <= (1.0 -d) * std::exp(d)) break;
        }
        const double q { 1.0 / r };
        const double f { (q + z) / (1.0 + q * z) };
        const double u3 { Storm::canonical_variate() };
        if (u3 > 0.5) return std::fmod(mu + std::acos(f), TAU);
        return std::fmod(mu - std::acos(f), TAU);
    }

    auto triangular_variate(double low, double high, double mode) -> double {
        if (low == high) return low;
        const double rand { Storm::canonical_variate() };
        const double mode_factor { (mode - low) / (high - low) };
        if (rand > mode_factor) return high + (low - high) * std::sqrt((1.0 - rand) * (1.0 - mode_factor));
        return low + (high - low) * std::sqrt(rand * mode_factor);
    }
    
} // end namespace
