#include "Eigen/Eigen"

#ifndef FUNCEXPR
#define FUNCEXPR return a;
#endif

namespace NMSPC
{
    template<typename Arg1, typename Arg2>
    struct binary_op_base
    {
        typedef Arg1 first_argument_type;
        typedef Arg2 second_argument_type;
    };

    template<typename LhsScalar, typename RhsScalar>
    struct FUNCNAME : binary_op_base<LhsScalar, RhsScalar>
    {
        typedef typename Eigen::ScalarBinaryOpTraits<LhsScalar, RhsScalar, FUNCNAME>::ReturnType result_type;
        EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE result_type operator() (const LhsScalar& a, const RhsScalar& b) const
        {
            FUNCEXPR
        }

        template<typename Packet>
        EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE Packet packetOp(const Packet& a, const Packet& b) const
        {
            FUNCEXPR
        }

        template<typename Packet>
        EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE result_type predux(const Packet& a) const
        {
            return a;
        }
    };
}

template<typename LhsType, typename RhsType>
EIGEN_DEVICE_FUNC
EIGEN_STRONG_INLINE
const Eigen::Matrix<typename LhsType::Scalar, LhsType::RowsAtCompileTime, LhsType::ColsAtCompileTime>
FUNCNAME(const Eigen::MatrixBase<LhsType>& derived, const Eigen::MatrixBase<RhsType>& otherDerived)
{
    typedef LhsType::Scalar LhsScalar;
    typedef RhsType::Scalar RhsScalar;
    typedef const Eigen::Matrix<LhsScalar, LhsType::RowsAtCompileTime, LhsType::ColsAtCompileTime> BinaryApllyLhsType;
    typedef const Eigen::Matrix<RhsScalar, RhsType::RowsAtCompileTime, RhsType::ColsAtCompileTime> BinaryApllyRhsType;

    return Eigen::CwiseBinaryOp
    <
        NMSPC::FUNCNAME<LhsScalar, RhsScalar>, BinaryApllyLhsType, BinaryApllyRhsType
    >(derived, otherDerived).eval();
}
