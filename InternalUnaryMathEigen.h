namespace NMSPC
{
    template<typename Scalar> struct ScalarOperation
    {
        typedef typename Eigen::NumTraits<Scalar>::Real result_type;
        EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE const result_type operator() (const Scalar& a) const
        {
            FUNCEXPR
        }

        template<typename Packet>
        EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE const Packet packetOp(const Packet& a) const
        {
            FUNCEXPR
        }
    };
}

template <typename Derived>
EIGEN_DEVICE_FUNC
EIGEN_STRONG_INLINE
const Eigen::Matrix<typename Derived::Scalar, Derived::RowsAtCompileTime, Derived::ColsAtCompileTime>
FUNCNAME(const Eigen::MatrixBase<Derived>& derived)
{
    typedef Derived::Scalar Scalar;
    return Eigen::CwiseUnaryOp
    <
        NMSPC::ScalarOperation<Scalar>,
        const Eigen::Matrix<Scalar, Derived::RowsAtCompileTime, Derived::ColsAtCompileTime>
    >(derived).eval();
}
